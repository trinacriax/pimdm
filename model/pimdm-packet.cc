/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 University of Trento, Italy
 *                    University of California, Los Angeles, U.S.A.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Source:  http://www.ietf.org/rfc/rfc3973.txt
 *
 * Authors: Alessandro Russo <russo@disi.unitn.it>
 *          University of Trento, Italy
 *          University of California, Los Angeles U.S.A.
 */

/// \brief	This file implements the PIM DM packet headers and all the functions needed for their manipulation.
#include "pimdm-packet.h"
#include <ns3/assert.h>
#include <ns3/log.h>
#include <ns3/object-base.h>

namespace ns3
{
  namespace pimdm
  {

    NS_LOG_COMPONENT_DEFINE("PIMDMHeader");

    NS_OBJECT_ENSURE_REGISTERED(PIMHeader);

    PIMHeader::PIMHeader () :
        m_version(0), m_type(PIM_HELLO), m_reserved(0), m_checksum(0)
    {
    }

    PIMHeader::~PIMHeader ()
    {
    }

    TypeId
    PIMHeader::GetTypeId (void)
    {
      static TypeId tid = TypeId("ns3::pimdm::PIMHeader").SetParent<Header>().AddConstructor<PIMHeader>();
      return tid;
    }
    TypeId
    PIMHeader::GetInstanceTypeId (void) const
    {
      return GetTypeId();
    }

    uint32_t
    PIMHeader::GetSerializedSize (void) const
    {
      uint32_t size = PIM_DM_HEADER_SIZE;
      switch (m_type)
        {
        case PIM_HELLO:
          //NS_LOG_DEBUG ("Hello Message Size: " << size << " + " << m_pim_message.hello.GetSerializedSize ());
          size += m_pim_message.hello.GetSerializedSize();
          break;
        case PIM_JP:
          size += m_pim_message.joinPrune.GetSerializedSize();
          break;
        case PIM_ASSERT:
          size += m_pim_message.assert.GetSerializedSize();
          break;
        case PIM_GRAFT:
          size += m_pim_message.graft.GetSerializedSize();
          break;
        case PIM_GRAFT_ACK:
          size += m_pim_message.graftAck.GetSerializedSize();
          break;
        case PIM_STATE_REF:
          size += m_pim_message.stateRefresh.GetSerializedSize();
          break;
        default:
          {
            NS_ASSERT(false);
            break;
          }
        }
      //std::cout << "PIMHeader Size "<< size << "\n";
      return size;
    }

    void
    PIMHeader::Print (std::ostream &os) const
    {
      os << "PIM Ver. " << (uint16_t) m_version;
      os << " Type " << (uint16_t) m_type;
      os << " Reserved " << (uint16_t) m_reserved;
      os << " Checksum " << m_checksum << "\n";
    }

    void
    PIMHeader::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      uint16_t header = m_version << 12 | m_type << 8 | m_reserved;
      i.WriteHtonU32(0);
      switch (m_type)
        {
        case PIM_HELLO:
          {
            m_pim_message.hello.Serialize(i);
//	  std::cout << "Serialize H\n";
            break;
          }
        case PIM_JP:
          m_pim_message.joinPrune.Serialize(i);
//	  std::cout << "Serialize J\n";
          break;
        case PIM_ASSERT:
          m_pim_message.assert.Serialize(i);
//	  std::cout << "Serialize A\n";
          break;
        case PIM_GRAFT:
          m_pim_message.graft.Serialize(i);
//	  std::cout << "Serialize G\n";
          break;
        case PIM_GRAFT_ACK:
          m_pim_message.graftAck.Serialize(i);
//	  std::cout << "Serialize GA\n";
          break;
        case PIM_STATE_REF:
          m_pim_message.stateRefresh.Serialize(i);
//	  std::cout << "Serialize S\n";
          break;
        default:
          {
            NS_ASSERT(false);
            break;
          }
        }
      i = start;
      i.Next(4);
      uint16_t checksum = i.CalculateIpChecksum(GetSerializedSize() - 4, 0);
      i = start;
      i.WriteHtonU16(header);
      i.WriteHtonU16(checksum);
    }

    uint32_t
    PIMHeader::Deserialize (Buffer::Iterator start)
    {
      Buffer::Iterator i = start;
      uint16_t checksum = 0;
      uint32_t size = PIM_DM_HEADER_SIZE;
      uint16_t ver_type = i.ReadNtohU16();
      m_version = m_reserved = m_checksum = 0;
      m_version = (uint8_t) ((ver_type & 0xf000) >> 12); 	// 11110000 00000000
      m_type = PIMType((ver_type & 0xf00) >> 8); // 00001111 00000000
      NS_ASSERT(m_type >= PIM_HELLO && m_type<=PIM_STATE_REF);
      m_reserved = (uint8_t) (ver_type & 0xff);		// 00000000 11111111
      m_checksum = i.ReadNtohU16();			// 00000000 00000000 11111111 11111111
      uint32_t message_size = i.GetSize();
      NS_ASSERT(message_size >0);
      switch (m_type)
        {
        case PIM_HELLO:
          size += m_pim_message.hello.Deserialize(i, message_size - size);
          break;
        case PIM_JP:
          size += m_pim_message.joinPrune.Deserialize(i, message_size - size);
          break;
        case PIM_ASSERT:
          size += m_pim_message.assert.Deserialize(i, message_size - size);
          break;
        case PIM_GRAFT:
          size += m_pim_message.graft.Deserialize(i, message_size - size);
          break;
        case PIM_GRAFT_ACK:
          size += m_pim_message.graftAck.Deserialize(i, message_size - size);
          break;
        case PIM_STATE_REF:
          size += m_pim_message.stateRefresh.Deserialize(i, message_size - size);
          break;
        default:
          {
            NS_ASSERT(false);
            break;
          }
        }
      i = start;
      i.Next(4);
      checksum = i.CalculateIpChecksum(GetSerializedSize() - 4, 0);
      NS_ASSERT_MSG(checksum == m_checksum, "Checksum error");
      return size;
    }

// -------------------- ENCODED UNICAST ADDRESS --------------------

    uint32_t
    PIMHeader::EncodedUnicast::GetSerializedSize (void) const
    {
      return PIM_DM_ENC_UNI;
    }

    void
    PIMHeader::EncodedUnicast::Print (std::ostream &os) const
    {
      os << " AddFam. = " << (uint16_t) this->m_addressFamily << " Enc.Type = " << (uint16_t) this->m_encodingType
          << " Unic.Addr. = " << this->m_unicastAddress << "\n";
    }

    void
    PIMHeader::EncodedUnicast::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      i.WriteU8(this->m_addressFamily);
      i.WriteU8(this->m_encodingType);
      i.WriteHtonU32(this->m_unicastAddress.Get());
    }

    uint32_t
    PIMHeader::EncodedUnicast::Deserialize (Buffer::Iterator start, uint32_t messageSize)
    {
      Buffer::Iterator i = start;
      NS_ASSERT(messageSize == PIM_DM_ENC_UNI);
      this->m_addressFamily = i.ReadU8();
      this->m_encodingType = i.ReadU8();
      this->m_unicastAddress = Ipv4Address(i.ReadNtohU32());
      return PIM_DM_ENC_UNI;
    }

// -------------------- ENCODED GROUP ADDRESS --------------------

    uint32_t
    PIMHeader::EncodedGroup::GetSerializedSize (void) const
    {
      return PIM_DM_ENC_GRP;
    }

    void
    PIMHeader::EncodedGroup::Print (std::ostream &os) const
    {
      os << " AddFam. = " << (uint16_t) this->m_addressFamily << " Enc.Type = " << (uint16_t) this->m_encodingType
          << " B = " << (uint16_t) this->m_B << " Reserved = " << (uint16_t) this->m_reserved << " Z = "
          << (uint16_t) this->m_Z << " MaskLen = " << (uint16_t) this->m_maskLength << " GroupAddress "
          << this->m_groupAddress << "\n";
    }

    void
    PIMHeader::EncodedGroup::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      i.WriteU8(this->m_addressFamily);
      i.WriteU8(this->m_encodingType);
      uint8_t BRZ = this->m_B << 7 | (this->m_reserved << 1 & 0x7e) | this->m_Z;
      i.WriteU8(BRZ);
      i.WriteU8(this->m_maskLength);
      i.WriteHtonU32(this->m_groupAddress.Get());
    }

    uint32_t
    PIMHeader::EncodedGroup::Deserialize (Buffer::Iterator start, uint32_t messageSize)
    {
      Buffer::Iterator i = start;
      uint16_t size = 0;
      NS_ASSERT(messageSize == PIM_DM_ENC_GRP);
      this->m_addressFamily = i.ReadU8();
      this->m_encodingType = i.ReadU8();
      uint8_t BRZ = i.ReadU8();
      this->m_B = (BRZ & 0x80) >> 7;
      this->m_reserved = (BRZ & 0x7e) >> 1;
      this->m_Z = (BRZ & 0x01);
      this->m_maskLength = i.ReadU8();
      size += 4;
      this->m_groupAddress = Ipv4Address(i.ReadNtohU32());
      size += sizeof(Ipv4Address);
      return size;
    }

// -------------------- ENCODED SOURCE ADDRESS --------------------

    uint32_t
    PIMHeader::EncodedSource::GetSerializedSize (void) const
    {
      return PIM_DM_ENC_SRC;
    }

    void
    PIMHeader::EncodedSource::Print (std::ostream &os) const
    {
      os << " AddFam. = " << (uint16_t) this->m_addressFamily << " Enc.Type = " << (uint16_t) this->m_encodingType
          << " Reserved = " << (uint16_t) this->m_reserved << " S = " << (uint16_t) this->m_S << " W = "
          << (uint16_t) this->m_W << " R = " << (uint16_t) this->m_R << " MaskLen = " << (uint16_t) this->m_maskLength
          << " SourceAddress " << this->m_sourceAddress << "\n";
    }

    void
    PIMHeader::EncodedSource::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      i.WriteU8(this->m_addressFamily);
      i.WriteU8(this->m_encodingType);
      uint8_t RSWR = this->m_reserved << 3 | (this->m_S << 2 & 0x04) | (this->m_W << 1 & 0x02) | (this->m_R & 0x01);
      i.WriteU8(RSWR);
      i.WriteU8(this->m_maskLength);
      i.WriteHtonU32(this->m_sourceAddress.Get());
    }

    uint32_t
    PIMHeader::EncodedSource::Deserialize (Buffer::Iterator start, uint32_t messageSize)
    {
      Buffer::Iterator i = start;
      uint16_t size = 0;
      NS_ASSERT(messageSize == PIM_DM_ENC_GRP);
      this->m_addressFamily = i.ReadU8();
      this->m_encodingType = i.ReadU8();
      uint8_t RSWR = i.ReadU8();
      this->m_reserved = (RSWR & 0xf8) >> 3;
      this->m_S = (RSWR & 0x04) >> 2;
      this->m_W = (RSWR & 0x02) >> 1;
      this->m_R = (RSWR & 0x01);
      this->m_maskLength = i.ReadU8();
      size += 4;
      this->m_sourceAddress = Ipv4Address(i.ReadNtohU32());
      size += sizeof(Ipv4Address);
      return messageSize;
    }

// ---------------- PIM-DM HELLO Message -------------------------------

    uint32_t
    PIMHeader::HelloMessage::GetSerializedSize (void) const
    {
      uint32_t size = 0;
      for (std::vector<HelloEntry>::const_iterator iter = this->m_optionList.begin(); iter != this->m_optionList.end();
          iter++)
        {
          const HelloEntry &ot = *iter;
          size += 4; //OptionType + OptionLength
          size += ot.m_optionLength; // Length in byte
        }
      return size;
    }

    void
    PIMHeader::HelloMessage::Print (std::ostream &os) const
    {
      for (std::vector<HelloEntry>::const_iterator iter = this->m_optionList.begin(); iter != this->m_optionList.end();
          iter++)
        {
          const HelloEntry &he = *iter;
          os << "Type = " << he.m_optionType << ", Length = " << he.m_optionLength;
          switch (he.m_optionType)
            {
            case HelloHoldTime:
              {
                os << ", HoldTime = " << he.m_optionValue.holdTime.s_holdTime.GetSeconds() << "\n";
                break;
              }
            case LANPruneDelay:
              {
                NS_ASSERT(he.m_optionLength % 4 == 0);
                os << " T = " << (uint16_t) he.m_optionValue.lanPruneDelay.s_T << ", Prop. delay = "
                    << he.m_optionValue.lanPruneDelay.s_propagationDelay.GetMilliSeconds() << " ms, Interval = "
                    << he.m_optionValue.lanPruneDelay.s_overrideInterval.GetMilliSeconds() << " ms\n";
                break;
              }
            case GenerationID:
              {
                NS_ASSERT(he.m_optionLength % 4 == 0);
                os << " Gen.ID = " << he.m_optionValue.generationID.s_generatioID << "\n";
                break;
              }
            case StateRefreshCapable:
              {
                NS_ASSERT(he.m_optionLength % 4 == 0);
                os << " V = " << (uint16_t) he.m_optionValue.stateRefreshCapable.s_version << ", Interval = "
                    << (uint16_t) he.m_optionValue.stateRefreshCapable.s_interval << ", Reserved = "
                    << he.m_optionValue.stateRefreshCapable.s_reserved << "\n";
                break;
              }
            default:
              {
                NS_ASSERT(false);
                break;
              }
            }
        }
    }

    void
    PIMHeader::HelloMessage::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      for (std::vector<HelloEntry>::const_iterator iter = this->m_optionList.begin(); iter != this->m_optionList.end();
          iter++)
        {
          const HelloEntry &he = *iter;
          i.WriteHtonU16(he.m_optionType);
          switch (he.m_optionType)
            {
            case HelloHoldTime:
              {
                NS_ASSERT(he.m_optionLength == PIM_DM_HELLO_HOLDTIME);
                i.WriteHtonU16(PIM_DM_HELLO_HOLDTIME);
                i.WriteHtonU16((uint16_t) he.m_optionValue.holdTime.s_holdTime.GetSeconds());
                break;
              }
            case LANPruneDelay:
              {
                NS_ASSERT(he.m_optionLength == PIM_DM_HELLO_LANPRUNDELAY);
                i.WriteHtonU16(PIM_DM_HELLO_LANPRUNDELAY);
                i.WriteHtonU16(
                    he.m_optionValue.lanPruneDelay.s_T << 15
                        | he.m_optionValue.lanPruneDelay.s_propagationDelay.GetMilliSeconds());
                i.WriteHtonU16(he.m_optionValue.lanPruneDelay.s_overrideInterval.GetMilliSeconds());
                break;
              }
            case GenerationID:
              {
                NS_ASSERT(he.m_optionLength == PIM_DM_HELLO_GENERATIONID);
                i.WriteHtonU16(PIM_DM_HELLO_GENERATIONID);
                i.WriteHtonU32(he.m_optionValue.generationID.s_generatioID);
                break;
              }
            case StateRefreshCapable:
              {
                NS_ASSERT(he.m_optionLength == PIM_DM_HELLO_STATEREFRESH);
                i.WriteHtonU16(PIM_DM_HELLO_STATEREFRESH);
                i.WriteU8(he.m_optionValue.stateRefreshCapable.s_version);
                i.WriteU8(he.m_optionValue.stateRefreshCapable.s_interval);
                i.WriteHtonU16(he.m_optionValue.stateRefreshCapable.s_reserved);
                break;
              }
            default:
              {
                NS_ASSERT(false);
                break;
              }
            }
        }
    }

    uint32_t
    PIMHeader::HelloMessage::Deserialize (Buffer::Iterator start, uint32_t messageSize)
    {
      Buffer::Iterator i = start;
      NS_ASSERT(messageSize >= 4);
      this->m_optionList.clear();
      uint16_t helloSizeLeft = messageSize;
      while (helloSizeLeft)
        {
          HelloEntry he;
          NS_ASSERT(helloSizeLeft >= 4);
          he.m_optionType = OptionType(i.ReadNtohU16());
          he.m_optionLength = i.ReadNtohU16();
          helloSizeLeft -= PIM_DM_HELLO;
          switch (he.m_optionType)
            {
            case HelloHoldTime:
              {
                NS_ASSERT(he.m_optionLength == PIM_DM_HELLO_HOLDTIME);
                he.m_optionValue.holdTime.s_holdTime = Seconds(i.ReadNtohU16());
                helloSizeLeft -= PIM_DM_HELLO_HOLDTIME;
                break;
              }
            case LANPruneDelay:
              {
                NS_ASSERT(he.m_optionLength == PIM_DM_HELLO_LANPRUNDELAY);
                uint16_t tmp = i.ReadNtohU16();
                he.m_optionValue.lanPruneDelay.s_T = (uint8_t) ((tmp & 0x8000) >> 15);
                he.m_optionValue.lanPruneDelay.s_propagationDelay = MilliSeconds(tmp & 0x7fff);
                he.m_optionValue.lanPruneDelay.s_overrideInterval = MilliSeconds(i.ReadNtohU16());
                helloSizeLeft -= PIM_DM_HELLO_LANPRUNDELAY;
                break;
              }
            case GenerationID:
              {
                NS_ASSERT(he.m_optionLength == PIM_DM_HELLO_GENERATIONID);
                he.m_optionValue.generationID.s_generatioID = i.ReadNtohU32();
                helloSizeLeft -= PIM_DM_HELLO_GENERATIONID;
                break;
              }
            case StateRefreshCapable:
              {
                NS_ASSERT(he.m_optionLength == PIM_DM_HELLO_STATEREFRESH);
                he.m_optionValue.stateRefreshCapable.s_version = i.ReadU8();
                he.m_optionValue.stateRefreshCapable.s_interval = i.ReadU8();
                he.m_optionValue.stateRefreshCapable.s_reserved = i.ReadNtohU16();
                helloSizeLeft -= PIM_DM_HELLO_STATEREFRESH;
                break;
              }
            default:
              {
                NS_ASSERT(false);
                break;
              }
            }
          this->m_optionList.push_back(he);
        }
      return messageSize;
    }

// ---------------- PIM-DM JOIN PRUNE GRAFT Message ------------------------

    uint32_t
    PIMHeader::JoinPruneGraftMessage::GetSerializedSize (void) const
    {
      return PIM_DM_JPG;
    }

    void
    PIMHeader::JoinPruneGraftMessage::Print (std::ostream &os) const
    {
      this->m_upstreamNeighborAddr.Print(os);
      os << " Reserved = " << (uint16_t) this->m_reserved << " Num.Groups = " << (uint16_t) this->m_numGroups
          << " Holdtime = " << this->m_holdTime.GetSeconds() << "\n";
    }

    void
    PIMHeader::JoinPruneGraftMessage::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      this->m_upstreamNeighborAddr.Serialize(i);
      uint16_t size = this->m_upstreamNeighborAddr.GetSerializedSize();
      i.Next(size);
      i.WriteU8(this->m_reserved);
      i.WriteU8(this->m_numGroups);
      uint16_t hold = (uint16_t) this->m_holdTime.GetSeconds();
      i.WriteHtonU16(hold);
    }

    uint32_t
    PIMHeader::JoinPruneGraftMessage::Deserialize (Buffer::Iterator start, uint32_t messageSize)
    {
      Buffer::Iterator i = start;
      NS_ASSERT(messageSize == this->GetSerializedSize());
      uint16_t size = this->m_upstreamNeighborAddr.Deserialize(i, PIM_DM_ENC_UNI);
      i.Next(size);
      this->m_reserved = i.ReadU8();
      this->m_numGroups = i.ReadU8();
      uint16_t hold = i.ReadNtohU16();
      this->m_holdTime = Seconds(hold);
      size += 4;
      return size;
    }

// ---------------- PIM-DM MulticastGroupEntry Message ---------------------------

    uint32_t
    PIMHeader::MulticastGroupEntry::GetSerializedSize (void) const
    {
      uint32_t size = this->m_multicastGroupAddr.GetSerializedSize();
      size += 4;
      size += PIM_DM_ENC_SRC * this->m_numberJoinedSources;
      size += PIM_DM_ENC_SRC * this->m_numberPrunedSources;
      return size;
    }

    void
    PIMHeader::MulticastGroupEntry::Print (std::ostream &os) const
    {
      this->m_multicastGroupAddr.Print(os);
      os << " NumJoinSrc = " << m_numberJoinedSources << " NumPrunedSrt " << this->m_numberPrunedSources << "\n";
      for (std::vector<EncodedSource>::const_iterator iter = this->m_joinedSourceAddrs.begin();
          iter != this->m_joinedSourceAddrs.end(); iter++)
        iter->Print(os);
      for (std::vector<EncodedSource>::const_iterator iter = this->m_prunedSourceAddrs.begin();
          iter != this->m_prunedSourceAddrs.end(); iter++)
        iter->Print(os);
    }

    void
    PIMHeader::MulticastGroupEntry::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      this->m_multicastGroupAddr.Serialize(i);
      i.Next(this->m_multicastGroupAddr.GetSerializedSize());
      i.WriteHtonU16(this->m_numberJoinedSources);
      NS_ASSERT(this->m_numberJoinedSources == this->m_joinedSourceAddrs.size());
      i.WriteHtonU16(this->m_numberPrunedSources);
      NS_ASSERT(this->m_numberPrunedSources == this->m_prunedSourceAddrs.size());
      for (std::vector<EncodedSource>::const_iterator iter = this->m_joinedSourceAddrs.begin();
          iter != this->m_joinedSourceAddrs.end(); iter++)
        {
          iter->Serialize(i);
          i.Next(iter->GetSerializedSize());
        }
      for (std::vector<EncodedSource>::const_iterator iter = this->m_prunedSourceAddrs.begin();
          iter != this->m_prunedSourceAddrs.end(); iter++)
        {
          iter->Serialize(i);
          i.Next(iter->GetSerializedSize());
        }
    }

    uint32_t
    PIMHeader::MulticastGroupEntry::Deserialize (Buffer::Iterator start, uint32_t messageSize)
    {
      Buffer::Iterator i = start;
      uint16_t size = this->m_multicastGroupAddr.Deserialize(i, this->m_multicastGroupAddr.GetSerializedSize());
      i.Next(size);
      this->m_numberJoinedSources = i.ReadNtohU16();
      this->m_numberPrunedSources = i.ReadNtohU16();
      size += 4;
      for (uint16_t j = 0; j < this->m_numberJoinedSources; j++)
        {
          struct EncodedSource join;
          this->m_joinedSourceAddrs.push_back(join);
          uint16_t len = this->m_joinedSourceAddrs[j].GetSerializedSize();
          size += this->m_joinedSourceAddrs[j].Deserialize(i, len);
          i.Next(this->m_joinedSourceAddrs[j].GetSerializedSize());
        }
      for (uint16_t j = 0; j < this->m_numberPrunedSources; j++)
        {
          struct EncodedSource prune;
          uint16_t len = prune.GetSerializedSize();
          size += prune.Deserialize(i, len);
          i.Next(prune.GetSerializedSize());
          this->m_prunedSourceAddrs.push_back(prune);
        }
      return size;
    }

// ---------------- PIM-DM JOIN PRUNE Message ---------------------------

    uint32_t
    PIMHeader::JoinPruneMessage::GetSerializedSize (void) const
    {
      uint32_t size = this->m_joinPruneMessage.GetSerializedSize();
      for (std::vector<struct MulticastGroupEntry>::const_iterator iter = this->m_multicastGroups.begin();
          iter != this->m_multicastGroups.end(); iter++)
        size += iter->GetSerializedSize();
      return size;
    }

    void
    PIMHeader::JoinPruneMessage::Print (std::ostream &os) const
    {
      this->m_joinPruneMessage.Print(os);
      for (std::vector<struct MulticastGroupEntry>::const_iterator iter = this->m_multicastGroups.begin();
          iter != this->m_multicastGroups.end(); iter++)
        iter->Print(os);
    }

    void
    PIMHeader::JoinPruneMessage::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      this->m_joinPruneMessage.Serialize(i);
      i.Next(this->m_joinPruneMessage.GetSerializedSize());
      for (std::vector<struct MulticastGroupEntry>::const_iterator iter = this->m_multicastGroups.begin();
          iter != this->m_multicastGroups.end(); iter++)
        {
          iter->Serialize(i);
          i.Next(iter->GetSerializedSize());
        }
    }

    uint32_t
    PIMHeader::JoinPruneMessage::Deserialize (Buffer::Iterator start, uint32_t messageSize)
    {
      Buffer::Iterator i = start;
      uint16_t size = this->m_joinPruneMessage.Deserialize(i, PIM_DM_JPG);
      i.Next(size);
      for (uint8_t j = 0; j < (uint16_t) this->m_joinPruneMessage.m_numGroups; j++)
        {
          MulticastGroupEntry mge;
          this->m_multicastGroups.push_back(mge);
          uint16_t len = this->m_multicastGroups[j].Deserialize(i, i.GetSize());
          i.Next(this->m_multicastGroups[j].GetSerializedSize());
          size += len;
        }
      return size;
    }

// ---------------- PIM-DM GRAFT Message -------------------------------

    uint32_t
    PIMHeader::GraftMessage::GetSerializedSize (void) const
    {
      uint32_t size = this->m_joinPruneMessage.GetSerializedSize();
      for (std::vector<struct MulticastGroupEntry>::const_iterator iter = this->m_multicastGroups.begin();
          iter != this->m_multicastGroups.end(); iter++)
        size += iter->GetSerializedSize();
      return size;
    }

    void
    PIMHeader::GraftMessage::Print (std::ostream &os) const
    {
      this->m_joinPruneMessage.Print(os);
      for (std::vector<struct MulticastGroupEntry>::const_iterator iter = this->m_multicastGroups.begin();
          iter != this->m_multicastGroups.end(); iter++)
        iter->Print(os);
    }

    void
    PIMHeader::GraftMessage::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      this->m_joinPruneMessage.Serialize(i);
      i.Next(this->m_joinPruneMessage.GetSerializedSize());
      for (std::vector<struct MulticastGroupEntry>::const_iterator iter = this->m_multicastGroups.begin();
          iter != this->m_multicastGroups.end(); iter++)
        {
          iter->Serialize(i);
          i.Next(iter->GetSerializedSize());
        }
    }

    uint32_t
    PIMHeader::GraftMessage::Deserialize (Buffer::Iterator start, uint32_t messageSize)
    {
      Buffer::Iterator i = start;
      uint16_t size = this->m_joinPruneMessage.Deserialize(i, PIM_DM_JPG);
      i.Next(size);
      for (uint8_t j = 0; j < (uint16_t) this->m_joinPruneMessage.m_numGroups; j++)
        {
          MulticastGroupEntry mge;
          this->m_multicastGroups.push_back(mge);
          uint16_t len = this->m_multicastGroups[j].Deserialize(i, i.GetSize());
          i.Next(this->m_multicastGroups[j].GetSerializedSize());
          size += len;
        }
      return size;
    }

// ---------------- PIM-DM GRAFT-ACK Message -------------------------------

    uint32_t
    PIMHeader::GraftAckMessage::GetSerializedSize (void) const
    {
      uint32_t size = this->m_joinPruneMessage.GetSerializedSize();
      for (std::vector<struct MulticastGroupEntry>::const_iterator iter = this->m_multicastGroups.begin();
          iter != this->m_multicastGroups.end(); iter++)
        size += iter->GetSerializedSize();
      return size;
    }

    void
    PIMHeader::GraftAckMessage::Print (std::ostream &os) const
    {
      this->m_joinPruneMessage.Print(os);
      for (std::vector<struct MulticastGroupEntry>::const_iterator iter = this->m_multicastGroups.begin();
          iter != this->m_multicastGroups.end(); iter++)
        iter->Print(os);
    }

    void
    PIMHeader::GraftAckMessage::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      this->m_joinPruneMessage.Serialize(i);
      i.Next(this->m_joinPruneMessage.GetSerializedSize());
      for (std::vector<struct MulticastGroupEntry>::const_iterator iter = this->m_multicastGroups.begin();
          iter != this->m_multicastGroups.end(); iter++)
        {
          iter->Serialize(i);
          i.Next(iter->GetSerializedSize());
        }
    }

    uint32_t
    PIMHeader::GraftAckMessage::Deserialize (Buffer::Iterator start, uint32_t messageSize)
    {
      Buffer::Iterator i = start;
      uint16_t size = this->m_joinPruneMessage.Deserialize(i, PIM_DM_JPG);
      i.Next(size);
      for (uint8_t j = 0; j < (uint16_t) this->m_joinPruneMessage.m_numGroups; j++)
        {
          MulticastGroupEntry mge;
          this->m_multicastGroups.push_back(mge);
          uint16_t len = this->m_multicastGroups[j].Deserialize(i, i.GetSize());
          i.Next(this->m_multicastGroups[j].GetSerializedSize());
          size += len;
        }
      return size;
    }

// ---------------- PIM-DM ASSERT Message ------------------------

    uint32_t
    PIMHeader::AssertMessage::GetSerializedSize (void) const
    {
      return PIM_DM_ASSERT;
    }

    void
    PIMHeader::AssertMessage::Print (std::ostream &os) const
    {
      this->m_multicastGroupAddr.Print(os);
      this->m_sourceAddr.Print(os);
      os << "Dest=" << m_destination << " R = " << (uint16_t) this->m_R << " Metric Pref. = "
          << this->m_metricPreference << " Metric = " << this->m_metric << "\n";
    }

    void
    PIMHeader::AssertMessage::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      this->m_multicastGroupAddr.Serialize(i);
      i.Next(this->m_multicastGroupAddr.GetSerializedSize());
      this->m_sourceAddr.Serialize(i);
      i.Next(this->m_sourceAddr.GetSerializedSize());
      i.WriteHtonU32(this->m_destination.Get());
      i.WriteHtonU32(this->m_R << 31 | (this->m_metricPreference & 0x7FFFFFFF));
      i.WriteHtonU32(this->m_metric);
    }

    uint32_t
    PIMHeader::AssertMessage::Deserialize (Buffer::Iterator start, uint32_t messageSize)
    {
      Buffer::Iterator i = start;
      NS_ASSERT(messageSize == this->GetSerializedSize());
      uint16_t size = this->m_multicastGroupAddr.Deserialize(i, PIM_DM_ENC_GRP);
      i.Next(PIM_DM_ENC_GRP);
      size += this->m_sourceAddr.Deserialize(i, PIM_DM_ENC_UNI);
      i.Next(PIM_DM_ENC_UNI);
      m_destination = Ipv4Address(i.ReadNtohU32());
      uint32_t RM = i.ReadNtohU32();
      this->m_R = (RM & 0x80000000) >> 31;
      this->m_metricPreference = RM & 0x7FFFFFFF;
      size += 4;
      this->m_metric = i.ReadNtohU32();
      size += 4;
      return size;
    }

// ---------------- PIM-DM STATE REFRESH Message ------------------------

    uint32_t
    PIMHeader::StateRefreshMessage::GetSerializedSize (void) const
    {
      return PIM_DM_REFRESH;
    }

    void
    PIMHeader::StateRefreshMessage::Print (std::ostream &os) const
    {
      this->m_multicastGroupAddr.Print(os);
      this->m_sourceAddr.Print(os);
      this->m_originatorAddr.Print(os);
      os << " R = " << (uint16_t) this->m_R << " Metric Pref. = " << this->m_metricPreference << " Metric = "
          << this->m_metric << " MaskLen = " << (uint16_t) this->m_maskLength << " TTL = " << (uint16_t) this->m_ttl
          << " P = " << (uint16_t) this->m_P << " N = " << (uint16_t) this->m_N << " O = " << (uint16_t) this->m_O
          << " Reserved = " << (uint16_t) this->m_reserved << " Interval = " << (uint16_t) this->m_interval << "\n";
    }

    void
    PIMHeader::StateRefreshMessage::Serialize (Buffer::Iterator start) const
    {
      Buffer::Iterator i = start;
      this->m_multicastGroupAddr.Serialize(i);
      i.Next(this->m_multicastGroupAddr.GetSerializedSize());
      this->m_sourceAddr.Serialize(i);
      i.Next(this->m_sourceAddr.GetSerializedSize());
      this->m_originatorAddr.Serialize(i);
      i.Next(this->m_originatorAddr.GetSerializedSize());
      i.WriteHtonU32((this->m_R & 0x1) << 31 | (this->m_metricPreference & 0x7fffffff));
      i.WriteHtonU32(this->m_metric);
      i.WriteU8(this->m_maskLength);
      i.WriteU8(this->m_ttl);
      i.WriteU8(this->m_P << 7 | (this->m_N & 0x01) << 6 | (this->m_O & 0x01) << 5 | (this->m_reserved & 0x1f));
      i.WriteU8(this->m_interval);
    }

    uint32_t
    PIMHeader::StateRefreshMessage::Deserialize (Buffer::Iterator start, uint32_t messageSize)
    {
      Buffer::Iterator i = start;
      NS_ASSERT(messageSize == this->GetSerializedSize());
      uint16_t size = this->m_multicastGroupAddr.Deserialize(i, PIM_DM_ENC_GRP);
      i.Next(PIM_DM_ENC_GRP);
      size += this->m_sourceAddr.Deserialize(i, PIM_DM_ENC_UNI);
      i.Next(PIM_DM_ENC_UNI);
      size += this->m_originatorAddr.Deserialize(i, PIM_DM_ENC_UNI);
      i.Next(PIM_DM_ENC_UNI);
      uint32_t RM = i.ReadNtohU32();
      this->m_R = (RM & 0x80000000) >> 31;
      this->m_metricPreference = RM & 0x7FFFFFFF;
      size += 4;
      this->m_metric = i.ReadNtohU32();
      size += 4;
      this->m_maskLength = i.ReadU8();
      this->m_ttl = i.ReadU8();
      uint8_t PNOR = i.ReadU8();
      this->m_P = PNOR >> 7;
      this->m_N = (PNOR & 0x40) >> 6;
      this->m_O = (PNOR & 0x20) >> 5;
      this->m_reserved = (PNOR & 0x1f);
      this->m_interval = i.ReadU8();
      size += 4;
      return size;
    }

  } // namespace pimdm
} // namespace ns3
