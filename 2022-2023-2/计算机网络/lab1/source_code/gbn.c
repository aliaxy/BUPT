#include <stdio.h>
#include <string.h>

#include "datalink.h"
#include "protocol.h"

#define DATA_TIMER 2000 // 重传计时器
#define ACK_TIMER 1100  // ACK计时器
#define MAX_SEQ 7       // 帧序号最大值
#define inc(k)                                                                 \
  if (k < MAX_SEQ)                                                             \
    k++;                                                                       \
  else                                                                         \
    k = 0;

typedef unsigned char frame_kind;      // 帧类型
typedef unsigned char seq_nr;          // 帧序号
typedef unsigned char packet[PKT_LEN]; // 数据包

typedef struct FRAME {  // 帧格式
  frame_kind kind;      // 帧类型
  seq_nr ack;           // ACK序号
  seq_nr seq;           // 帧序号
  packet info;          // 帧数据
  unsigned int padding; // CRC填充
} frame;

static int phl_ready = 0;        // 物理层状态
static unsigned char no_nak = 1; // ACK状态

static seq_nr next_frame_to_send;  // 发送窗口下一个发送
static seq_nr ack_expected;        // 发送窗口希望的ACK
static seq_nr frame_expected;      // 接收窗口希望的帧序号
static frame r;                    // 接受的帧
static packet buffer[MAX_SEQ + 1]; // 数据缓存
static seq_nr nbuffered;           // 已经缓存的帧数目

static unsigned char between(seq_nr a, seq_nr b, seq_nr c) {
  return ((a <= b && b < c) || (c < a && b < c) || (c < a && a <= b));
}

static void put_frame(unsigned char *frame, int len) {
  *(unsigned int *)(frame + len) = crc32(frame, len);
  send_frame(frame, len + 4);
  phl_ready = 0;
}

static void send_data_frame(frame_kind fk, seq_nr frame_nr,
                            seq_nr frame_expected, packet buffer[]) {
  frame s;
  s.kind = fk;
  s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
  stop_ack_timer();
  if (fk == FRAME_DATA) {
    s.seq = frame_nr;
    memcpy(s.info, buffer[frame_nr], PKT_LEN);
    dbg_frame("Send DATA %d %d, ID %d\n", s.seq, s.ack, *(short *)s.info);
    put_frame((unsigned char *)&s, 3 + PKT_LEN);
    start_timer(frame_nr, DATA_TIMER);
  } else if (fk == FRAME_ACK) {
    dbg_frame("Send ACK  %d\n", s.ack);
    put_frame((unsigned char *)&s, 2);
  } else if (fk == FRAME_NAK) {
    dbg_frame("Send NAK  %d\n", (s.ack + 1) % (MAX_SEQ + 1));
    no_nak = 0;
    put_frame((unsigned char *)&s, 2);
  }
}

int main(int argc, char **argv) {
  int event, arg;
  int len = 0;

  protocol_init(argc, argv);
  lprintf("Designed by Aliaxy, build: " __DATE__ "  "__TIME__
          "\n");

  disable_network_layer();
  ack_expected = 0;
  next_frame_to_send = 0;
  frame_expected = 0;
  nbuffered = 0;

  for (;;) {
    if ((ack_expected + nbuffered) % (MAX_SEQ + 1) == next_frame_to_send) {
      if (nbuffered < MAX_SEQ && phl_ready) {
        enable_network_layer();
      } else {
        disable_network_layer();
      }
    } else {
      dbg_event("%d-%d\n", (ack_expected + nbuffered) % (MAX_SEQ + 1),
                next_frame_to_send);

      send_data_frame(FRAME_DATA, next_frame_to_send, frame_expected, buffer);
      inc(next_frame_to_send);
      disable_network_layer();
    }

    event = wait_for_event(&arg);

    switch (event) {
    case NETWORK_LAYER_READY:
      get_packet(buffer[next_frame_to_send]);
      nbuffered++;
      send_data_frame(FRAME_DATA, next_frame_to_send, frame_expected, buffer);
      inc(next_frame_to_send);
      break;

    case PHYSICAL_LAYER_READY:
      phl_ready = 1;
      break;

    case FRAME_RECEIVED:
      len = recv_frame((unsigned char *)&r, sizeof r);
      if (len < 5 || crc32((unsigned char *)&r, len) != 0) {
        dbg_event("**** Receiver Error, Bad CRC Checksum\n", len);
        if (no_nak)
          send_data_frame(FRAME_NAK, 0, frame_expected, buffer);
        break;
      }

      if (r.kind == FRAME_DATA) {
        dbg_frame("Recv DATA %d %d, ID %d--%dbyte\n", r.seq, r.ack,
                  *(short *)r.info, len);
        if (r.seq == frame_expected) {
          dbg_frame("Truee index.\n");
          put_packet(r.info, len - 7);
          inc(frame_expected);
          no_nak = 1;
          start_ack_timer(ACK_TIMER);
        } else if (no_nak) {
          dbg_frame("Wrong seqnr %d received,send NAK.\n", r.seq);
          send_data_frame(FRAME_NAK, 0, frame_expected, buffer);
        }
      }

      if (r.kind == FRAME_NAK && (r.ack + 1) % (MAX_SEQ + 1) == ack_expected) {
        dbg_frame("Recv NAK  %d --%dbyte\n", (r.ack + 1) % (MAX_SEQ + 1), len);

        next_frame_to_send = ack_expected;

        for (int i = 0; i < nbuffered; ++i) {
          send_data_frame(FRAME_DATA, next_frame_to_send, frame_expected,
                          buffer);
          inc(next_frame_to_send);
        }
      }

      while (between(ack_expected, r.ack, next_frame_to_send)) {
        nbuffered--;
        stop_timer(ack_expected);
        inc(ack_expected);
      }

      break;

    case DATA_TIMEOUT:
      dbg_event("---- DATA %d timeout\n", arg);
      next_frame_to_send = ack_expected;
      for (int i = 0; i < nbuffered; i++) {
        send_data_frame(FRAME_DATA, next_frame_to_send, frame_expected, buffer);
        inc(next_frame_to_send);
      }
      break;
    case ACK_TIMEOUT:
      send_data_frame(FRAME_ACK, 0, frame_expected, buffer);
      break;
    }
  }
}
