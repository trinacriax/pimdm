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

/// \brief	This header file declares the Protocol Independent Multicast - Dense Mode (PIM-DM), RFC 3973
#ifndef __PIM_DM_HEADER_H__
#define __PIM_DM_HEADER_H__

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdint.h>
#include <stdlib.h>

#include "pimdm-common.h"
#include <ns3/header.h>
#include <ns3/ipv4-address.h>
#include <ns3/enum.h>
#include <ns3/nstime.h>

const uint32_t PIM_NATIVE_ENCODING = 0;		///< PIM native encoding.
const uint32_t PIM_DM_HEADER_SIZE = 4;  	///< PIM header size in bytes.
const uint32_t PIM_DM_ENC_UNI = 6;		///< PIM encoded unicast message size in bytes.
const uint32_t PIM_DM_ENC_GRP = 8;		///< PIM encoded group message size in bytes.
const uint32_t PIM_DM_ENC_SRC = 8;		///< PIM encoded source message size in bytes.
const uint32_t PIM_DM_HELLO = 4;			///< PIM hello message size in bytes.
const uint32_t PIM_DM_HELLO_HOLDTIME = 2;	///< PIM holdtime size in bytes.
const uint32_t PIM_DM_HELLO_LANPRUNDELAY = 4;	///< PIM lan prune delay size in bytes.
const uint32_t PIM_DM_HELLO_GENERATIONID = 4;	///< PIM generation id size in bytes.
const uint32_t PIM_DM_HELLO_STATEREFRESH = 4;	///< PIM state refresh size in bytes.
const uint32_t PIM_DM_JPG = (PIM_DM_ENC_UNI + 4);	///< PIM join-prune-graft message size in bytes.
const uint32_t PIM_DM_ASSERT = (PIM_DM_ENC_GRP + PIM_DM_ENC_UNI + 8 + 4);	///< PIM assert message size in bytes.
const uint32_t PIM_DM_REFRESH = (PIM_DM_ENC_GRP + PIM_DM_ENC_UNI + PIM_DM_ENC_UNI + 24);///< PIM refresh message size in bytes.
const uint32_t PIM_IP_PROTOCOL_NUM = 103; ///< PIM IP Protocol number defined by IANA. http://www.iana.org/assignments/protocol-numbers/protocol-numbers.xml

namespace ns3
{
  namespace pimdm
  {

    const Ipv4Address ALL_PIM_ROUTERS4 = Ipv4Address("224.0.0.13");

    enum PIMType
    {
      PIM_HELLO = 0,   //!< Hello Message
//  PIM_REG  = 1,		//!< (PIM-SM only)
//  PIM_REG_STOP  = 2,//!< (PIM-SM only)
      PIM_JP = 3,
//  PIM_BOOTSTRAP = 4,//!< (PIM-SM only)
      PIM_ASSERT = 5,
      PIM_GRAFT = 6,
      PIM_GRAFT_ACK = 7,
//  PIM_CANDIDATE_RP_ADV = 8,//!< (PIM-SM only)
      PIM_STATE_REF = 9,
    };

    /**
     * \ingroup PIM-DM.
     *
     * \brief PIM-DM Message format types.
     *
     * Defining all the PIM-DM messages.
     */

//	0               1               2               3
//	0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|PIM Ver| Type  |   Reserved    |           Checksum            |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//	PIM Ver PIM version number is 2.
    class PIMHeader : public Header
    {
      public:
        PIMHeader ();
        virtual
        ~PIMHeader ();

        ///\name PIM-DM main Header methods
        //\{
        uint8_t
        GetVersion () const
        {
          return m_version;
        }
        void
        SetVersion (uint8_t version)
        {
          m_version = version;
        }

        PIMType
        GetType () const
        {
          return m_type;
        }
        void
        SetType (PIMType type)
        {
          m_type = type;
        }

        uint8_t
        GetReserved () const
        {
          return m_reserved;
        }
        void
        SetReserved (uint8_t reserved)
        {
          m_reserved = reserved;
        }

        uint16_t
        GetChecksum () const
        {
          return m_checksum;
        }
        void
        SetChecksum (uint8_t checksum)
        {
          m_checksum = checksum;
        }
        //\}

      private:
        /// PIM Ver PIM version number is 2.
        uint8_t m_version;
        /// Type. Types for specific PIM messages.
        PIMType m_type;
        /// Reserved. Set to zero on transmission.  Ignored upon receipt.
        uint8_t m_reserved;
        ///  Checksum.
        ///    The checksum is the standard IP checksum; i.e., the 16 bit one's
        ///    complement of the one's complement sum of the entire PIM message.
        ///    For computing checksum, the checksum field is zeroed.
        ///
        ///    For IPv6, the checksum also includes the IPv6 "pseudo-header", as
        ///    specified in RFC 2460, Section 8.1 [5].
        uint16_t m_checksum;

      public:
        ///\name Header serialization/deserialization
        //\{
        static TypeId
        GetTypeId (void);
        virtual TypeId
        GetInstanceTypeId (void) const;
        virtual void
        Print (std::ostream &os) const;
        virtual uint32_t
        GetSerializedSize (void) const;
        virtual void
        Serialize (Buffer::Iterator start) const;
        virtual uint32_t
        Deserialize (Buffer::Iterator start);
        //\}

//	An Encoded Unicast Address has the following format:
//
//	0               1               2               3
//	0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|  Addr Family  | Encoding Type |     Unicast Address
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	     Unicast Address            |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
        struct EncodedUnicast
        {
            ///  The PIM Address Family of the 'Unicast Address' field of this address.
            ///  PIM Address Family.  Registration Procedures. IESG Approval
            ///    Reference [RFC3973]
            ///    Value 	Description 	Reference
            ///      0-127	Same meaning as Address Family Numbers. See http://www.iana.org/assignments/address-family-numbers
            ///    128-250	Unassigned
            ///    251-255	Reserved for Private Use	[RFC3973]
            uint8_t m_addressFamily;

            /// The type of encoding used with a specific Address Family.
            ///	Registration Procedures
            ///
            ///	    IETF Review
            ///
            ///	Reference
            ///	    [RFC4601][RFC5384]
            ///
            ///	Value 	Description 	Reference
            ///	0	native encoding for the address family	[RFC4601]
            ///	1	native encoding for the address family, but with zero or more PIM Join Attributes present	[RFC5384]
            ///	2-255	Unassigned
            uint8_t m_encodingType;

            /// The unicast address as represented by the given Address Family and Encoding Type.
            Ipv4Address m_unicastAddress; // TODO: Just IPv4-> can be improved to get the corresponding addressFamily

            void
            Print (std::ostream &os) const;

            uint32_t
            GetSerializedSize (void) const;
            void
            Serialize (Buffer::Iterator start) const;
            uint32_t
            Deserialize (Buffer::Iterator start, uint32_t messageSize);
        };

//	An Encoded Group address has the following format:
//
//	0               1               2               3
//	0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|  Addr Family  | Encoding Type |B| Reserved  |Z|  Mask Len     |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                    Group Multicast Address                    |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

        struct EncodedGroup
        {
            ///  The PIM Address Family of the 'Unicast Address' field of this address.
            uint8_t m_addressFamily;

            /// The type of encoding used with a specific Address Family.
            uint8_t m_encodingType;

            /// Indicates that the group range should use Bidirectional PIM.
            ///   Transmitted as zero; ignored upon receipt.
            uint8_t m_B;

            /// Transmitted as zero.
            uint8_t m_reserved;

            /// Indicates that the group range is an admin scope zone.  This is
            ///   used in the Bootstrap Router Mechanism [18] only.  For all other
            ///   purposes, this bit is set to zero and ignored on receipt.
            uint8_t m_Z;

            /// The mask length field is 8 bits.  The value is the number of
            ///   contiguous left justified one bits used as a mask, which, combined
            ///   with the address, describes a range of addresses.  It is less than
            ///   or equal to the address length in bits for the given Address Family
            ///   and Encoding Type.  If the message is sent for a single address
            ///   then the mask length MUST equal the address length.  PIM-DM routers
            ///   MUST only send for a single address.
            uint8_t m_maskLength;

            /// The address of the multicast group.
            Ipv4Address m_groupAddress;

            void
            Print (std::ostream &os) const;
            uint32_t
            GetSerializedSize (void) const;
            void
            Serialize (Buffer::Iterator start) const;
            uint32_t
            Deserialize (Buffer::Iterator start, uint32_t messageSize);
        };

//	0               1               2               3
//	0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|  Addr Family  | Encoding Type |  Rsrvd  |S|W|R|  Mask Len     |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                         Source Address                        |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

        struct EncodedSource
        {
            /// The PIM Address Family of the 'Unicast Address' field of this address.
            uint8_t m_addressFamily;

            /// The type of encoding used with a specific Address Family.
            uint8_t m_encodingType;

            /// Transmitted as zero.
            uint8_t m_reserved;

            /// The Sparse Bit.  Set to 0 for PIM-DM.  Ignored upon receipt.
            uint8_t m_S;

            /// The Wild Card Bit.  Set to 0 for PIM-DM.  Ignored upon receipt.
            uint8_t m_W;

            /// The Rendezvous Point Tree bit.  Set to 0 for PIM-DM.  Ignored upon receipt.
            uint8_t m_R;

            /// The mask length field is 8 bits.  The value is the number of
            ///   contiguous left justified one bits used as a mask, which, combined
            ///   with the address, describes a range of addresses.  It is less than
            ///   or equal to the address length in bits for the given Address Family
            ///   and Encoding Type.  If the message is sent for a single address
            ///   then the mask length MUST equal the address length.  PIM-DM routers
            ///   MUST only send for a single address.
            uint8_t m_maskLength;

            /// The Source address.
            Ipv4Address m_sourceAddress;

            void
            Print (std::ostream &os) const;
            uint32_t
            GetSerializedSize (void) const;
            void
            Serialize (Buffer::Iterator start) const;
            uint32_t
            Deserialize (Buffer::Iterator start, uint32_t messageSize);
        };

//	0               1               2               3
//	0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|PIM Ver| Type  |   Reserved    |           Checksum            |   GENERIC
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|          Option Type          |         Option Length         |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                         Option Value                          |
//	|                              ...                              |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                               .                               |
//	|                               .                               |
//	|                               .                               |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|          Option Type          |         Option Length         |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                         Option Value                          |
//	|                              ...                              |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

        struct HelloMessage
        {
            ///    The type of option given in the Option Value field.  Available types are as follows:
            //     0              Reserved
            //     1              Hello Hold Time
            //     2              LAN Prune Delay
            //     3 - 16         Reserved
            //     17             To be assigned by IANA
            //     18             Deprecated and SHOULD NOT be used
            //     19             DR Priority (PIM-SM Only)
            //     20             Generation ID
            //     21             State Refresh Capable
            //     22             Bidir Capable
            //     23 - 65000     To be assigned by IANA
            //     65001 - 65535  Reserved for Private Use [9]
            enum OptionType
            {
              // 0 Reserved
              Reserved = 0,
              HelloHoldTime = 1,
              LANPruneDelay = 2,
              // 3 - 16 Reserved
              AssignedIANA = 17,
              // 18 Deprecated and SHOLD NOT be used
              // 19 DR Priority (PIM-SM Only)
              GenerationID = 20,
              StateRefreshCapable = 21,
              BidirCapable = 22,
            // 23 - 65000     To be assigned by IANA
            // 65001 - 65535  Reserved for Private Use [9]
            };

            struct HelloEntry
            {
//		0               1               2               3
//		0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//		|            Type = 1           |           Length = 2          |
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//		|            Hold Time          |
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
                /**
                 * Hold Time is the number of seconds a receiver MUST keep the neighbor
                 * reachable.  If the Hold Time is set to '0xffff', the receiver of this
                 * message never times out the neighbor.  This may be used with dial-
                 * on-demand links to avoid keeping the link up with periodic Hello
                 * messages.  Furthermore, if the Holdtime is set to '0', the
                 * information is timed out immediately.  The Hello Hold Time option
                 * MUST be used by PIM-DM routers.
                 */

                struct HoldTime
                {
                    Time s_holdTime;
                };

//		0               1               2               3
//		0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//		|            Type = 2           |           Length = 4          |
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//		|T|       LAN Prune Delay       |       Override Interval       |
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
                /**
                 * The LAN_Prune_Delay option is used to tune the prune propagation
                 * delay on multi-access LANs.  The T bit is used by PIM-SM and SHOULD
                 * be set to 0 by PIM-DM routers and ignored upon receipt.  The LAN
                 * Delay and Override Interval fields are time intervals in units of
                 * milliseconds and are used to tune the value of the J/P Override
                 * Interval and its derived timer values.  Section 4.3.5 describes how
                 * these values affect the behavior of a router.  The LAN Prune Delay
                 * SHOULD be used by PIM-DM routers.
                 *
                 */

                struct LanPruneDelay
                {
                    uint8_t s_T;
                    Time s_propagationDelay;
                    Time s_overrideInterval;
                };
//		0               1               2               3
//		0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//		|           Type = 20           |           Length = 4          |
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//		|                         Generation ID                         |
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
                /**
                 * Generation ID is a random value for the interface on which the Hello
                 * message is sent.  The Generation ID is regenerated whenever PIM
                 * forwarding is started or restarted on the interface.  The Generation
                 * ID option MAY be used by PIM-DM routers.
                 *
                 */

                struct GenerationID
                {
                    uint32_t s_generatioID;
                };

//		0               1               2               3
//		0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//		|           Type = 21           |           Length = 4          |
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//		|  Version = 1  |   Interval    |            Reserved           |
//		+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
                /**
                 * The Interval field is the router's configured State Refresh Interval in seconds.
                 * The Reserved field is set to zero and ignored upon receipt.
                 * The State Refresh Capable option MUST be used by State
                 * Refresh capable PIM-DM routers.
                 *
                 */

                struct StateRefreshCapable
                {
                    uint8_t s_version;
                    uint8_t s_interval;
                    uint16_t s_reserved;
                };

                OptionType m_optionType;
                /// The length of the option in bytes.
                uint16_t m_optionLength;
                /// The value of the option.
                struct
                {
                    HoldTime holdTime;
                    LanPruneDelay lanPruneDelay;
                    GenerationID generationID;
                    StateRefreshCapable stateRefreshCapable;
                } m_optionValue;
            };

//            Ipv4Address m_destination;
            std::vector<HelloEntry> m_optionList;
            void
            Print (std::ostream &os) const;
            uint32_t
            GetSerializedSize (void) const;
            void
            Serialize (Buffer::Iterator start) const;
            uint32_t
            Deserialize (Buffer::Iterator start, uint32_t messageSize);
        };

//	0               1               2               3
//	0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Multicast Group Address 1 (Encoded Group Format)      |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|   Number of Joined Sources    |   Number of Pruned Sources    |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Joined Source Address 1 (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                               .                               |
//	|                               .                               |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Joined Source Address n (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Pruned Source Address 1 (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                               .                               |
//	|                               .                               |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Pruned Source Address n (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                               .                               |
//	|                               .                               |
//	|                               .                               |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

        struct MulticastGroupEntry
        {
            MulticastGroupEntry () :
                m_numberJoinedSources(0), m_numberPrunedSources(0)
            {
              m_joinedSourceAddrs.clear();
              m_prunedSourceAddrs.clear();
            }
            /// Multicast Group Address 1
            EncodedGroup m_multicastGroupAddr;

            /// Number of Joined Sources. Number of joined source addresses listed for a given group
            uint16_t m_numberJoinedSources;

            /// Number of Pruned Sources. Number of pruned source addresses listed for a group.
            uint16_t m_numberPrunedSources;

            /// Joined Source Addresses.
            /// This list contains the sources for a given group that the
            /// sending router will forward multicast datagrams from if received
            /// on the interface on which the Join/Prune message is sent.
            std::vector<EncodedSource> m_joinedSourceAddrs;

            /// Pruned Source Address.
            /// This list contains the sources for a given group that the sending
            /// router does not want to forward multicast datagrams from when
            /// received on the interface on which the Join/Prune message is sent.
            std::vector<EncodedSource> m_prunedSourceAddrs;

            void
            Print (std::ostream &os) const;
            uint32_t
            GetSerializedSize (void) const;
            void
            Serialize (Buffer::Iterator start) const;
            uint32_t
            Deserialize (Buffer::Iterator start, uint32_t messageSize);
        };

//	0               1               2               3
//	0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|PIM Ver| Type  |   Reserved    |           Checksum            |   GENERIC
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|        Upstream Neighbor Address (Encoded Unicast Format)     |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|   Reserved    |  Num Groups   |          Hold Time            |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//

        struct JoinPruneGraftMessage
        {
            /// Upstream Neighbor Address
            ///   The address of the upstream neighbor.  The format for this address
            ///   is given in the Encoded Unicast address in Section 4.7.2.  PIM-DM
            ///   routers MUST set this field to the RPF next hop
            EncodedUnicast m_upstreamNeighborAddr;

            /// Reserved. Transmitted as Zero, ignored on receipt.
            uint8_t m_reserved;

            /// Number of groups. The number of multicast group sets contained in the message
            uint8_t m_numGroups;

            /// Hold time. The amount of time a receiver must keep the Join/Prune state alive, in seconds.
            Time m_holdTime; //ignore for graft messages

            void
            Print (std::ostream &os) const;
            uint32_t
            GetSerializedSize (void) const;
            void
            Serialize (Buffer::Iterator start) const;
            uint32_t
            Deserialize (Buffer::Iterator start, uint32_t messageSize);
        };

//	0               1               2               3
//	0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|PIM Ver| Type  |   Reserved    |           Checksum            |   GENERIC
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|        Upstream Neighbor Address (Encoded Unicast Format)     |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|   Reserved    |  Num Groups   |          Hold Time            |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Multicast Group Address 1 (Encoded Group Format)      |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|   Number of Joined Sources    |   Number of Pruned Sources    |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Joined Source Address 1 (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                               .                               |
//	|                               .                               |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Joined Source Address n (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Pruned Source Address 1 (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                               .                               |
//	|                               .                               |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Pruned Source Address n (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                               .                               |
//	|                               .                               |
//	|                               .                               |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Multicast Group Address m (Encoded Group Format)      |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|   Number of Joined Sources    |   Number of Pruned Sources    |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Joined Source Address 1 (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                               .                               |
//	|                               .                               |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Joined Source Address n (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Pruned Source Address 1 (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                               .                               |
//	|                               .                               |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Pruned Source Address n (Encoded Source Format)       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

        struct JoinPruneMessage
        {

            struct JoinPruneGraftMessage m_joinPruneMessage;

            std::vector<struct MulticastGroupEntry> m_multicastGroups;

            void
            Print (std::ostream &os) const;
            uint32_t
            GetSerializedSize (void) const;
            void
            Serialize (Buffer::Iterator start) const;
            uint32_t
            Deserialize (Buffer::Iterator start, uint32_t messageSize);
        };

//	PIM Graft messages use the same format as Join/Prune messages, except
//	  that the Type field is set to 6.  The source address MUST be in the
//	  Join section of the message. The Hold Time field SHOULD be zero and
//	  SHOULD be ignored when a Graft is received.

        struct GraftMessage
        {

            struct JoinPruneGraftMessage m_joinPruneMessage;

            std::vector<struct MulticastGroupEntry> m_multicastGroups;

            void
            Print (std::ostream &os) const;
            uint32_t
            GetSerializedSize (void) const;
            void
            Serialize (Buffer::Iterator start) const;
            uint32_t
            Deserialize (Buffer::Iterator start, uint32_t messageSize);
        };
//	PIM Graft Ack messages are identical in format to the received Graft
//	  message, except that the Type field is set to 7.  The Upstream
//	  Neighbor Address field SHOULD be set to the sender of the Graft
//	  message and SHOULD be ignored upon receipt.

        struct GraftAckMessage
        {

            struct JoinPruneGraftMessage m_joinPruneMessage;

            std::vector<struct MulticastGroupEntry> m_multicastGroups;

            void
            Print (std::ostream &os) const;
            uint32_t
            GetSerializedSize (void) const;
            void
            Serialize (Buffer::Iterator start) const;
            uint32_t
            Deserialize (Buffer::Iterator start, uint32_t messageSize);
        };

//	0               1               2               3
//	0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|PIM Ver| Type  |   Reserved    |           Checksum            |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Multicast Group Address (Encoded Group Format)        |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|             Source Address (Encoded Unicast Format)           |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|R|                     Metric Preference                       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                             Metric                            |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

        struct AssertMessage
        {
            ///  The multicast group address in the Encoded Multicast address format given in Section 4.7.3.
            // Upstream Neighbor Address
            EncodedGroup m_multicastGroupAddr;

            /// The source address in the Encoded Unicast address format given in Section 4.7.2
            EncodedUnicast m_sourceAddr;

            /// The Rendezvous Point Tree bit. Set to 0 for PIM-DM.  Ignored upon receipt.
            uint8_t m_R;

            /// Metric Preference. The preference value assigned to the unicast routing protocol that provided the route to the source.
            uint32_t m_metricPreference;

            ///   Metric. The cost metric of the unicast route to the source. The metric is in units applicable to the unicast routing protocol used.
            uint32_t m_metric;

            /// Destination IP address
            Ipv4Address m_destination;

            void
            Print (std::ostream &os) const;
            uint32_t
            GetSerializedSize (void) const;
            void
            Serialize (Buffer::Iterator start) const;
            uint32_t
            Deserialize (Buffer::Iterator start, uint32_t messageSize);
        };

//	0               1               2               3
//	0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|PIM Ver| Type  |   Reserved    |           Checksum            |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|         Multicast Group Address (Encoded Group Format)        |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|             Source Address (Encoded Unicast Format)           |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|           Originator Address (Encoded Unicast Format)         |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|R|                     Metric Preference                       |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|                             Metric                            |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//	|    Masklen    |    TTL        |P|N|O|Reserved |   Interval    |
//	+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

        struct StateRefreshMessage
        {
            ///  The multicast group address in the Encoded Multicast address format given in Section 4.7.3.
            /// Upstream Neighbor Address
            struct EncodedGroup m_multicastGroupAddr;

            /// The source address in the Encoded Unicast address format given in Section 4.7.2
            struct EncodedUnicast m_sourceAddr;

            /// Originator Address. The address of the first hop router in the Encoded Unicast address format given in Section 4.7.2.
            struct EncodedUnicast m_originatorAddr;

            /// The Rendezvous Point Tree bit. Set to 0 for PIM-DM.  Ignored upon receipt.
            uint8_t m_R;

            /// Metric Preference. The preference value assigned to the unicast routing protocol that provided the route to the source.
            uint32_t m_metricPreference;

            /// Metric. The cost metric of the unicast route to the source. The metric is in units applicable to the unicast routing protocol used.
            uint32_t m_metric;

            /// Masklen. The length of the address mask of the unicast route to the source.
            uint8_t m_maskLength;

            /// TTL. Time To Live of the State Refresh message.  Decremented each time
            ///   the message is forwarded.  Note that this is different from the IP
            ///   Header TTL, which is always set to 1.
            uint8_t m_ttl;

            /// Prune indicator flag.  This MUST be set to 1 if the State Refresh
            /// is to be sent on a Pruned interface.  Otherwise, it MUST be set to 0.
            uint8_t m_P;

            /// Prune Now flag.  This SHOULD be set to 1 by the State Refresh
            ///     originator on every third State Refresh message and SHOULD be
            ///     ignored upon receipt.  This is for compatibility with earlier
            ///     versions of state refresh.
            uint8_t m_N;

            /// Assert Override flag.  This SHOULD be set to 1 by upstream routers
            ///     on a LAN if the Assert Timer (AT(S,G)) is not running and SHOULD be
            ///     ignored upon receipt.  This is for compatibility with earlier
            ///     versions of state refresh.
            uint8_t m_O;

            /// Reserved. Set to zero and ignored upon receipt.
            uint8_t m_reserved;

            /// Interval. Set by the originating router to the interval (in seconds) between
            ///     consecutive State Refresh messages for this (S,G) pair.
            uint8_t m_interval;

            void
            Print (std::ostream &os) const;
            uint32_t
            GetSerializedSize (void) const;
            void
            Serialize (Buffer::Iterator start) const;
            uint32_t
            Deserialize (Buffer::Iterator start, uint32_t messageSize);
        };

      private:
        struct
        {
            HelloMessage hello;
            JoinPruneMessage joinPrune;
            AssertMessage assert;
            GraftMessage graft;
            GraftAckMessage graftAck;
            StateRefreshMessage stateRefresh;
        } m_pim_message;

      public:

        HelloMessage&
        GetHelloMessage ()
        {
          if (m_type == 0)
            {
              m_type = PIM_HELLO;
            }
          else
            {
              NS_ASSERT(m_type == PIM_HELLO);
            }
          return m_pim_message.hello;
        }

        JoinPruneMessage&
        GetJoinPruneMessage ()
        {
          if (m_type == 0)
            {
              m_type = PIM_JP;
            }
          else
            {
              NS_ASSERT(m_type == PIM_JP);
            }
          return m_pim_message.joinPrune;
        }

        AssertMessage&
        GetAssertMessage ()
        {
          if (m_type == 0)
            {
              m_type = PIM_ASSERT;
            }
          else
            {
              NS_ASSERT(m_type == PIM_ASSERT);
            }
          return m_pim_message.assert;
        }

        GraftMessage&
        GetGraftMessage ()
        {
          if (m_type == 0)
            {
              m_type = PIM_GRAFT;
            }
          else
            {
              NS_ASSERT(m_type == PIM_GRAFT);
            }
          return m_pim_message.graft;
        }

        GraftAckMessage&
        GetGraftAckMessage ()
        {
          if (m_type == 0)
            {
              m_type = PIM_GRAFT_ACK;
            }
          else
            {
              NS_ASSERT(m_type == PIM_GRAFT_ACK);
            }
          return m_pim_message.graftAck;
        }

        StateRefreshMessage&
        GetStateRefreshMessage ()
        {
          if (m_type == 0)
            {
              m_type = PIM_STATE_REF;
            }
          else
            {
              NS_ASSERT(m_type == PIM_STATE_REF);
            }
          return m_pim_message.stateRefresh;
        }

    };

    static inline std::ostream&
    operator<< (std::ostream& os, const PIMHeader & packet)
    {
      packet.Print(os);
      return os;
    }

    typedef std::vector<PIMHeader> PIMMessageList;

    static inline std::ostream&
    operator<< (std::ostream& os, const PIMMessageList & messages)
    {
      os << "[";
      for (std::vector<PIMHeader>::const_iterator messageIter = messages.begin(); messageIter != messages.end();
          messageIter++)
        {
          messageIter->Print(os);
          if (messageIter + 1 != messages.end())
            os << ", ";
        }
      os << "]";
      return os;
    }

  } //end namespace pimdm
} //end namespace ns3
#endif /* __PIM_DM__HEADER_H__ */
