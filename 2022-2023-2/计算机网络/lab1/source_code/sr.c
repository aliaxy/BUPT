#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "datalink.h"
#include "protocol.h"

#define DATA_TIMER 6000             // 重传计时器
#define ACK_TIMER 5100              // ACK计时器
#define MAX_SEQ 43                  // 帧序号最大值
#define NR_BUFS ((MAX_SEQ + 1) / 2) // 窗口大小
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

static seq_nr next_frame_to_send; // 发送窗口下一个发送
static seq_nr ack_expected;       // 发送窗口希望的ACK
static seq_nr frame_expected;     // 接收窗口希望的帧序号
static seq_nr too_far;            // 接收窗口右端点的下一个
static frame r;                   // 接收的帧
static packet in_buf[NR_BUFS];    // 接收窗口缓冲
static packet out_buf[NR_BUFS];   // 发送窗口缓冲
static bool arrived[NR_BUFS];     // 记录完成的帧
static seq_nr nbuffered;          // 已经缓存的帧数目

/*
 * 判断某个序号是否在窗口内
 * a 左下标
 * b 判断的值
 * c 右下标的下一个
 */
static unsigned char between(seq_nr a, seq_nr b, seq_nr c) {
  return ((a <= b && b < c) || (c < a && b < c) || (c < a && a <= b));
}

/*
 * 发送帧添加校验位给物理层
 */
static void put_frame(unsigned char *frame, int len) {
  *(unsigned int *)(frame + len) = crc32(frame, len);
  send_frame(frame, len + 4);
  phl_ready = 0;
}

/*
 * 填充内容发送给物理层
 */

static void send_data_frame(frame_kind fk, seq_nr frame_nr,
                            seq_nr frame_expected, packet buffer[]) {
  frame s;
  s.kind = fk;
  s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);
  stop_ack_timer();

  if (fk == FRAME_DATA) {
    s.seq = frame_nr;
    memcpy(s.info, buffer[frame_nr % NR_BUFS], PKT_LEN);
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
  lprintf("Designed by aliaxy, build: " __DATE__ "  "__TIME__
          "\n");

  disable_network_layer();

  ack_expected = 0;
  next_frame_to_send = 0;
  frame_expected = 0;
  too_far = NR_BUFS;
  nbuffered = 0;
  for (int i = 0; i < NR_BUFS; i++) {
    arrived[i] = 0;
  }

  while (true) {
    event = wait_for_event(&arg);

    switch (event) {
    case NETWORK_LAYER_READY:
      nbuffered++;
      get_packet(out_buf[next_frame_to_send % NR_BUFS]);
      send_data_frame(FRAME_DATA, next_frame_to_send, frame_expected, out_buf);
      inc(next_frame_to_send);
      break;

    case PHYSICAL_LAYER_READY:
      phl_ready = 1;
      break;

    case FRAME_RECEIVED:
      len = recv_frame((unsigned char *)&r, sizeof(r));

      if (len < 6 || crc32((unsigned char *)&r, len) != 0) {
        dbg_event("**** Receiver Error(length=%d), Bad CRC Checksum\n", len);
        if (no_nak) {
          send_data_frame(FRAME_NAK, 0, frame_expected, out_buf);
        }
        break;
      }

      if (r.kind == FRAME_DATA) {
        dbg_frame("Recv DATA seq:%d ack:%d, ID %d |frame_e: %d  too_far:%d "
                  "--%dbyte\n",
                  r.seq, r.ack, *(short *)r.info, frame_expected, too_far, len);

        if ((r.seq != frame_expected) && no_nak) {
          dbg_event(" Recv frame is not lower bound, NAK sent back\n");
          send_data_frame(FRAME_NAK, 0, frame_expected, out_buf);
        }

        if (between(frame_expected, r.seq, too_far) &&
            (arrived[r.seq % NR_BUFS] == 0)) {
          arrived[r.seq % NR_BUFS] = 1;
          memcpy(in_buf[r.seq % NR_BUFS], r.info, PKT_LEN);
          while (arrived[frame_expected % NR_BUFS]) {
            dbg_event("Put packet to network layer seq:%d, ID: %d\n",
                      frame_expected,
                      *(short *)(in_buf[frame_expected % NR_BUFS]));
            put_packet(in_buf[frame_expected % NR_BUFS], PKT_LEN);
            arrived[frame_expected % NR_BUFS] = 0;
            no_nak = 1;
            inc(frame_expected);
            inc(too_far);
            start_ack_timer(ACK_TIMER);
          }
        }
      }

      if (r.kind == FRAME_NAK &&
          between(ack_expected, (r.ack + 1) % (MAX_SEQ + 1),
                  next_frame_to_send)) {
        dbg_frame("Recv NAK  %d --%dbyte\n", (r.ack + 1) % (MAX_SEQ + 1), len);

        send_data_frame(FRAME_DATA, (r.ack + 1) % (MAX_SEQ + 1), frame_expected,
                        out_buf);
      }

      while (between(ack_expected, r.ack, next_frame_to_send)) {
        nbuffered--;
        stop_timer(ack_expected);
        inc(ack_expected);
      }

      break;

    case DATA_TIMEOUT:
      dbg_event("---- DATA %d timeout, resend\n", arg);
      send_data_frame(FRAME_DATA, arg, frame_expected, out_buf);
      break;

    case ACK_TIMEOUT:
      send_data_frame(FRAME_ACK, 0, frame_expected, out_buf);
      break;
    }

    if (nbuffered < NR_BUFS && phl_ready) {
      enable_network_layer();
    } else {
      disable_network_layer();
    }
  }
}
