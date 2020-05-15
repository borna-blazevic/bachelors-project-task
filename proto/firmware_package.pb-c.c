/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: proto/firmware_package.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "proto/firmware_package.pb-c.h"
void   firmware_upgrade__srec_line__init
                     (FirmwareUpgrade__SrecLine         *message)
{
  static const FirmwareUpgrade__SrecLine init_value = FIRMWARE_UPGRADE__SREC_LINE__INIT;
  *message = init_value;
}
size_t firmware_upgrade__srec_line__get_packed_size
                     (const FirmwareUpgrade__SrecLine *message)
{
  assert(message->base.descriptor == &firmware_upgrade__srec_line__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t firmware_upgrade__srec_line__pack
                     (const FirmwareUpgrade__SrecLine *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &firmware_upgrade__srec_line__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t firmware_upgrade__srec_line__pack_to_buffer
                     (const FirmwareUpgrade__SrecLine *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &firmware_upgrade__srec_line__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
FirmwareUpgrade__SrecLine *
       firmware_upgrade__srec_line__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (FirmwareUpgrade__SrecLine *)
     protobuf_c_message_unpack (&firmware_upgrade__srec_line__descriptor,
                                allocator, len, data);
}
void   firmware_upgrade__srec_line__free_unpacked
                     (FirmwareUpgrade__SrecLine *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &firmware_upgrade__srec_line__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   firmware_upgrade__firmware_packet__init
                     (FirmwareUpgrade__FirmwarePacket         *message)
{
  static const FirmwareUpgrade__FirmwarePacket init_value = FIRMWARE_UPGRADE__FIRMWARE_PACKET__INIT;
  *message = init_value;
}
size_t firmware_upgrade__firmware_packet__get_packed_size
                     (const FirmwareUpgrade__FirmwarePacket *message)
{
  assert(message->base.descriptor == &firmware_upgrade__firmware_packet__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t firmware_upgrade__firmware_packet__pack
                     (const FirmwareUpgrade__FirmwarePacket *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &firmware_upgrade__firmware_packet__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t firmware_upgrade__firmware_packet__pack_to_buffer
                     (const FirmwareUpgrade__FirmwarePacket *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &firmware_upgrade__firmware_packet__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
FirmwareUpgrade__FirmwarePacket *
       firmware_upgrade__firmware_packet__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (FirmwareUpgrade__FirmwarePacket *)
     protobuf_c_message_unpack (&firmware_upgrade__firmware_packet__descriptor,
                                allocator, len, data);
}
void   firmware_upgrade__firmware_packet__free_unpacked
                     (FirmwareUpgrade__FirmwarePacket *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &firmware_upgrade__firmware_packet__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   firmware_upgrade__acknowledge__init
                     (FirmwareUpgrade__Acknowledge         *message)
{
  static const FirmwareUpgrade__Acknowledge init_value = FIRMWARE_UPGRADE__ACKNOWLEDGE__INIT;
  *message = init_value;
}
size_t firmware_upgrade__acknowledge__get_packed_size
                     (const FirmwareUpgrade__Acknowledge *message)
{
  assert(message->base.descriptor == &firmware_upgrade__acknowledge__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t firmware_upgrade__acknowledge__pack
                     (const FirmwareUpgrade__Acknowledge *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &firmware_upgrade__acknowledge__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t firmware_upgrade__acknowledge__pack_to_buffer
                     (const FirmwareUpgrade__Acknowledge *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &firmware_upgrade__acknowledge__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
FirmwareUpgrade__Acknowledge *
       firmware_upgrade__acknowledge__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (FirmwareUpgrade__Acknowledge *)
     protobuf_c_message_unpack (&firmware_upgrade__acknowledge__descriptor,
                                allocator, len, data);
}
void   firmware_upgrade__acknowledge__free_unpacked
                     (FirmwareUpgrade__Acknowledge *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &firmware_upgrade__acknowledge__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   firmware_upgrade__reject__init
                     (FirmwareUpgrade__Reject         *message)
{
  static const FirmwareUpgrade__Reject init_value = FIRMWARE_UPGRADE__REJECT__INIT;
  *message = init_value;
}
size_t firmware_upgrade__reject__get_packed_size
                     (const FirmwareUpgrade__Reject *message)
{
  assert(message->base.descriptor == &firmware_upgrade__reject__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t firmware_upgrade__reject__pack
                     (const FirmwareUpgrade__Reject *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &firmware_upgrade__reject__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t firmware_upgrade__reject__pack_to_buffer
                     (const FirmwareUpgrade__Reject *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &firmware_upgrade__reject__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
FirmwareUpgrade__Reject *
       firmware_upgrade__reject__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (FirmwareUpgrade__Reject *)
     protobuf_c_message_unpack (&firmware_upgrade__reject__descriptor,
                                allocator, len, data);
}
void   firmware_upgrade__reject__free_unpacked
                     (FirmwareUpgrade__Reject *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &firmware_upgrade__reject__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
void   firmware_upgrade__ready__init
                     (FirmwareUpgrade__Ready         *message)
{
  static const FirmwareUpgrade__Ready init_value = FIRMWARE_UPGRADE__READY__INIT;
  *message = init_value;
}
size_t firmware_upgrade__ready__get_packed_size
                     (const FirmwareUpgrade__Ready *message)
{
  assert(message->base.descriptor == &firmware_upgrade__ready__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t firmware_upgrade__ready__pack
                     (const FirmwareUpgrade__Ready *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &firmware_upgrade__ready__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t firmware_upgrade__ready__pack_to_buffer
                     (const FirmwareUpgrade__Ready *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &firmware_upgrade__ready__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
FirmwareUpgrade__Ready *
       firmware_upgrade__ready__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (FirmwareUpgrade__Ready *)
     protobuf_c_message_unpack (&firmware_upgrade__ready__descriptor,
                                allocator, len, data);
}
void   firmware_upgrade__ready__free_unpacked
                     (FirmwareUpgrade__Ready *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &firmware_upgrade__ready__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor firmware_upgrade__srec_line__field_descriptors[5] =
{
  {
    "record_type",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(FirmwareUpgrade__SrecLine, record_type),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "byte_count",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(FirmwareUpgrade__SrecLine, byte_count),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "address",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(FirmwareUpgrade__SrecLine, address),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "data",
    4,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(FirmwareUpgrade__SrecLine, data),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "checksum",
    5,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(FirmwareUpgrade__SrecLine, checksum),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned firmware_upgrade__srec_line__field_indices_by_name[] = {
  2,   /* field[2] = address */
  1,   /* field[1] = byte_count */
  4,   /* field[4] = checksum */
  3,   /* field[3] = data */
  0,   /* field[0] = record_type */
};
static const ProtobufCIntRange firmware_upgrade__srec_line__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 5 }
};
const ProtobufCMessageDescriptor firmware_upgrade__srec_line__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "firmware_upgrade.srec_line",
  "SrecLine",
  "FirmwareUpgrade__SrecLine",
  "firmware_upgrade",
  sizeof(FirmwareUpgrade__SrecLine),
  5,
  firmware_upgrade__srec_line__field_descriptors,
  firmware_upgrade__srec_line__field_indices_by_name,
  1,  firmware_upgrade__srec_line__number_ranges,
  (ProtobufCMessageInit) firmware_upgrade__srec_line__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor firmware_upgrade__firmware_packet__field_descriptors[3] =
{
  {
    "sent_checksum",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_INT32,
    0,   /* quantifier_offset */
    offsetof(FirmwareUpgrade__FirmwarePacket, sent_checksum),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "line",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(FirmwareUpgrade__FirmwarePacket, line),
    &firmware_upgrade__srec_line__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "message_checksum",
    3,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(FirmwareUpgrade__FirmwarePacket, message_checksum),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned firmware_upgrade__firmware_packet__field_indices_by_name[] = {
  1,   /* field[1] = line */
  2,   /* field[2] = message_checksum */
  0,   /* field[0] = sent_checksum */
};
static const ProtobufCIntRange firmware_upgrade__firmware_packet__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor firmware_upgrade__firmware_packet__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "firmware_upgrade.firmware_packet",
  "FirmwarePacket",
  "FirmwareUpgrade__FirmwarePacket",
  "firmware_upgrade",
  sizeof(FirmwareUpgrade__FirmwarePacket),
  3,
  firmware_upgrade__firmware_packet__field_descriptors,
  firmware_upgrade__firmware_packet__field_indices_by_name,
  1,  firmware_upgrade__firmware_packet__number_ranges,
  (ProtobufCMessageInit) firmware_upgrade__firmware_packet__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor firmware_upgrade__acknowledge__field_descriptors[1] =
{
  {
    "acknowledge",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(FirmwareUpgrade__Acknowledge, acknowledge),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned firmware_upgrade__acknowledge__field_indices_by_name[] = {
  0,   /* field[0] = acknowledge */
};
static const ProtobufCIntRange firmware_upgrade__acknowledge__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor firmware_upgrade__acknowledge__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "firmware_upgrade.acknowledge",
  "Acknowledge",
  "FirmwareUpgrade__Acknowledge",
  "firmware_upgrade",
  sizeof(FirmwareUpgrade__Acknowledge),
  1,
  firmware_upgrade__acknowledge__field_descriptors,
  firmware_upgrade__acknowledge__field_indices_by_name,
  1,  firmware_upgrade__acknowledge__number_ranges,
  (ProtobufCMessageInit) firmware_upgrade__acknowledge__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor firmware_upgrade__reject__field_descriptors[1] =
{
  {
    "reject",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(FirmwareUpgrade__Reject, reject),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned firmware_upgrade__reject__field_indices_by_name[] = {
  0,   /* field[0] = reject */
};
static const ProtobufCIntRange firmware_upgrade__reject__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor firmware_upgrade__reject__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "firmware_upgrade.reject",
  "Reject",
  "FirmwareUpgrade__Reject",
  "firmware_upgrade",
  sizeof(FirmwareUpgrade__Reject),
  1,
  firmware_upgrade__reject__field_descriptors,
  firmware_upgrade__reject__field_indices_by_name,
  1,  firmware_upgrade__reject__number_ranges,
  (ProtobufCMessageInit) firmware_upgrade__reject__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCFieldDescriptor firmware_upgrade__ready__field_descriptors[1] =
{
  {
    "ready",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_BYTES,
    0,   /* quantifier_offset */
    offsetof(FirmwareUpgrade__Ready, ready),
    NULL,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned firmware_upgrade__ready__field_indices_by_name[] = {
  0,   /* field[0] = ready */
};
static const ProtobufCIntRange firmware_upgrade__ready__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor firmware_upgrade__ready__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "firmware_upgrade.ready",
  "Ready",
  "FirmwareUpgrade__Ready",
  "firmware_upgrade",
  sizeof(FirmwareUpgrade__Ready),
  1,
  firmware_upgrade__ready__field_descriptors,
  firmware_upgrade__ready__field_indices_by_name,
  1,  firmware_upgrade__ready__number_ranges,
  (ProtobufCMessageInit) firmware_upgrade__ready__init,
  NULL,NULL,NULL    /* reserved[123] */
};
