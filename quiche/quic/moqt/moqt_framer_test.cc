// Copyright (c) 2023 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "quiche/quic/moqt/moqt_framer.h"

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"
#include "quiche/quic/moqt/moqt_messages.h"
#include "quiche/quic/moqt/test_tools/moqt_test_message.h"
#include "quiche/quic/platform/api/quic_expect_bug.h"
#include "quiche/quic/platform/api/quic_test.h"
#include "quiche/common/quiche_buffer_allocator.h"
#include "quiche/common/simple_buffer_allocator.h"

namespace moqt::test {

struct MoqtFramerTestParams {
  MoqtFramerTestParams(MoqtMessageType message_type, bool uses_web_transport)
      : message_type(message_type), uses_web_transport(uses_web_transport) {}
  MoqtMessageType message_type;
  bool uses_web_transport;
};

std::vector<MoqtFramerTestParams> GetMoqtFramerTestParams() {
  std::vector<MoqtFramerTestParams> params;
  std::vector<MoqtMessageType> message_types = {
      MoqtMessageType::kObjectStream,
      MoqtMessageType::kSubscribe,
      MoqtMessageType::kSubscribeOk,
      MoqtMessageType::kSubscribeError,
      MoqtMessageType::kUnsubscribe,
      MoqtMessageType::kSubscribeFin,
      MoqtMessageType::kSubscribeRst,
      MoqtMessageType::kAnnounce,
      MoqtMessageType::kAnnounceOk,
      MoqtMessageType::kAnnounceError,
      MoqtMessageType::kUnannounce,
      MoqtMessageType::kGoAway,
      MoqtMessageType::kClientSetup,
      MoqtMessageType::kServerSetup,
      MoqtMessageType::kStreamHeaderTrack,
      MoqtMessageType::kStreamHeaderGroup,
  };
  std::vector<bool> uses_web_transport_bool = {
      false,
      true,
  };
  for (const MoqtMessageType message_type : message_types) {
    if (message_type == MoqtMessageType::kClientSetup) {
      for (const bool uses_web_transport : uses_web_transport_bool) {
        params.push_back(
            MoqtFramerTestParams(message_type, uses_web_transport));
      }
    } else {
      // All other types are processed the same for either perspective or
      // transport.
      params.push_back(MoqtFramerTestParams(message_type, true));
    }
  }
  return params;
}

std::string ParamNameFormatter(
    const testing::TestParamInfo<MoqtFramerTestParams>& info) {
  return MoqtMessageTypeToString(info.param.message_type) + "_" +
         (info.param.uses_web_transport ? "WebTransport" : "QUIC");
}

quiche::QuicheBuffer SerializeObject(MoqtFramer& framer,
                                     const MoqtObject& message,
                                     absl::string_view payload,
                                     bool is_first_in_stream) {
  MoqtObject adjusted_message = message;
  adjusted_message.payload_length = payload.size();
  quiche::QuicheBuffer header =
      framer.SerializeObjectHeader(adjusted_message, is_first_in_stream);
  if (header.empty()) {
    return quiche::QuicheBuffer();
  }
  return quiche::QuicheBuffer::Copy(
      quiche::SimpleBufferAllocator::Get(),
      absl::StrCat(header.AsStringView(), payload));
}

class MoqtFramerTest
    : public quic::test::QuicTestWithParam<MoqtFramerTestParams> {
 public:
  MoqtFramerTest()
      : message_type_(GetParam().message_type),
        webtrans_(GetParam().uses_web_transport),
        buffer_allocator_(quiche::SimpleBufferAllocator::Get()),
        framer_(buffer_allocator_, GetParam().uses_web_transport) {}

  std::unique_ptr<TestMessageBase> MakeMessage(MoqtMessageType message_type) {
    return CreateTestMessage(message_type, webtrans_);
  }

  quiche::QuicheBuffer SerializeMessage(
      TestMessageBase::MessageStructuredData& structured_data) {
    switch (message_type_) {
      case MoqtMessageType::kObjectStream:
      case MoqtMessageType::kStreamHeaderTrack:
      case MoqtMessageType::kStreamHeaderGroup: {
        MoqtObject data = std::get<MoqtObject>(structured_data);
        return SerializeObject(framer_, data, "foo", true);
      }
      case MoqtMessageType::kSubscribe: {
        auto data = std::get<MoqtSubscribe>(structured_data);
        return framer_.SerializeSubscribe(data);
      }
      case MoqtMessageType::kSubscribeOk: {
        auto data = std::get<MoqtSubscribeOk>(structured_data);
        return framer_.SerializeSubscribeOk(data);
      }
      case MoqtMessageType::kSubscribeError: {
        auto data = std::get<MoqtSubscribeError>(structured_data);
        return framer_.SerializeSubscribeError(data);
      }
      case MoqtMessageType::kUnsubscribe: {
        auto data = std::get<MoqtUnsubscribe>(structured_data);
        return framer_.SerializeUnsubscribe(data);
      }
      case MoqtMessageType::kSubscribeFin: {
        auto data = std::get<MoqtSubscribeFin>(structured_data);
        return framer_.SerializeSubscribeFin(data);
      }
      case MoqtMessageType::kSubscribeRst: {
        auto data = std::get<MoqtSubscribeRst>(structured_data);
        return framer_.SerializeSubscribeRst(data);
      }
      case MoqtMessageType::kAnnounce: {
        auto data = std::get<MoqtAnnounce>(structured_data);
        return framer_.SerializeAnnounce(data);
      }
      case moqt::MoqtMessageType::kAnnounceOk: {
        auto data = std::get<MoqtAnnounceOk>(structured_data);
        return framer_.SerializeAnnounceOk(data);
      }
      case moqt::MoqtMessageType::kAnnounceError: {
        auto data = std::get<MoqtAnnounceError>(structured_data);
        return framer_.SerializeAnnounceError(data);
      }
      case MoqtMessageType::kUnannounce: {
        auto data = std::get<MoqtUnannounce>(structured_data);
        return framer_.SerializeUnannounce(data);
      }
      case moqt::MoqtMessageType::kGoAway: {
        auto data = std::get<MoqtGoAway>(structured_data);
        return framer_.SerializeGoAway(data);
      }
      case MoqtMessageType::kClientSetup: {
        auto data = std::get<MoqtClientSetup>(structured_data);
        return framer_.SerializeClientSetup(data);
      }
      case MoqtMessageType::kServerSetup: {
        auto data = std::get<MoqtServerSetup>(structured_data);
        return framer_.SerializeServerSetup(data);
      }
      default:
        // kObjectDatagram is a totally different code path.
        return quiche::QuicheBuffer();
    }
  }

  MoqtMessageType message_type_;
  bool webtrans_;
  quiche::SimpleBufferAllocator* buffer_allocator_;
  MoqtFramer framer_;
};

INSTANTIATE_TEST_SUITE_P(MoqtFramerTests, MoqtFramerTest,
                         testing::ValuesIn(GetMoqtFramerTestParams()),
                         ParamNameFormatter);

TEST_P(MoqtFramerTest, OneMessage) {
  auto message = MakeMessage(message_type_);
  auto structured_data = message->structured_data();
  auto buffer = SerializeMessage(structured_data);
  EXPECT_EQ(buffer.size(), message->total_message_size());
  EXPECT_EQ(buffer.AsStringView(), message->PacketSample());
}

class MoqtFramerSimpleTest : public quic::test::QuicTest {
 public:
  MoqtFramerSimpleTest()
      : buffer_allocator_(quiche::SimpleBufferAllocator::Get()),
        framer_(buffer_allocator_, /*web_transport=*/true) {}

  quiche::SimpleBufferAllocator* buffer_allocator_;
  MoqtFramer framer_;
};

TEST_F(MoqtFramerSimpleTest, GroupMiddler) {
  auto header = std::make_unique<StreamHeaderGroupMessage>();
  auto buffer1 = SerializeObject(
      framer_, std::get<MoqtObject>(header->structured_data()), "foo", true);
  EXPECT_EQ(buffer1.size(), header->total_message_size());
  EXPECT_EQ(buffer1.AsStringView(), header->PacketSample());

  auto middler = std::make_unique<StreamMiddlerGroupMessage>();
  auto buffer2 = SerializeObject(
      framer_, std::get<MoqtObject>(middler->structured_data()), "bar", false);
  EXPECT_EQ(buffer2.size(), middler->total_message_size());
  EXPECT_EQ(buffer2.AsStringView(), middler->PacketSample());
}

TEST_F(MoqtFramerSimpleTest, TrackMiddler) {
  auto header = std::make_unique<StreamHeaderTrackMessage>();
  auto buffer1 = SerializeObject(
      framer_, std::get<MoqtObject>(header->structured_data()), "foo", true);
  EXPECT_EQ(buffer1.size(), header->total_message_size());
  EXPECT_EQ(buffer1.AsStringView(), header->PacketSample());

  auto middler = std::make_unique<StreamMiddlerTrackMessage>();
  auto buffer2 = SerializeObject(
      framer_, std::get<MoqtObject>(middler->structured_data()), "bar", false);
  EXPECT_EQ(buffer2.size(), middler->total_message_size());
  EXPECT_EQ(buffer2.AsStringView(), middler->PacketSample());
}

TEST_F(MoqtFramerSimpleTest, BadObjectInput) {
  MoqtObject object = {
      /*subscribe_id=*/3,
      /*track_alias=*/4,
      /*group_id=*/5,
      /*object_id=*/6,
      /*object_send_order=*/7,
      /*forwarding_preference=*/MoqtForwardingPreference::kObject,
      /*payload_length=*/std::nullopt,
  };
  quiche::QuicheBuffer buffer;
  object.forwarding_preference = MoqtForwardingPreference::kDatagram;
  EXPECT_QUIC_BUG(buffer = framer_.SerializeObjectHeader(object, false),
                  "must be first");
  EXPECT_TRUE(buffer.empty());
  object.forwarding_preference = MoqtForwardingPreference::kGroup;
  EXPECT_QUIC_BUG(buffer = framer_.SerializeObjectHeader(object, false),
                  "requires knowing the object length");
  EXPECT_TRUE(buffer.empty());
}

TEST_F(MoqtFramerSimpleTest, Datagram) {
  auto datagram = std::make_unique<ObjectDatagramMessage>();
  MoqtObject object = {
      /*subscribe_id=*/3,
      /*track_alias=*/4,
      /*group_id=*/5,
      /*object_id=*/6,
      /*object_send_order=*/7,
      /*forwarding_preference=*/MoqtForwardingPreference::kObject,
      /*payload_length=*/std::nullopt,
  };
  std::string payload = "foo";
  quiche::QuicheBuffer buffer;
  buffer = framer_.SerializeObjectDatagram(object, payload);
  EXPECT_EQ(buffer.size(), datagram->total_message_size());
  EXPECT_EQ(buffer.AsStringView(), datagram->PacketSample());
}

}  // namespace moqt::test
