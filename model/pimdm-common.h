/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 University of Trento, Italy
 * 					  University of California, Los Angeles, U.S.A.
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
 *
 * Authors: Alessandro Russo <russo@disi.unitn.it>
 *          University of Trento, Italy
 *          University of California, Los Angeles U.S.A.
 */

/// \brief	This header file declares the common data structures for PIM-DM protocol.
#ifndef __PIM_DM_COMMON_H__
#define __PIM_DM_COMMON_H__

#include <list>
#include <math.h>
#include <ns3/ipv4-address.h>
#include <ns3/timer.h>

namespace ns3
{
  namespace pimdm
  {

    enum AddressFamily
    {
      AF_Reserved = 0,
      AF_IPv4 = 1,
      AF_IPv6 = 2,
      AF_NSAP = 3,
      AF_HDLC = 4,
      AF_BBN_1822 = 5,
      AF_A802 = 6,
      AF_E163 = 7,
      AF_E164 = 8, // (SMDS, Frame Relay, ATM)
      AF_F69 = 9, // (Telex)
      AF_X121 = 10, //(X.25, Frame Relay)
      AF_IPX = 11,
      AF_Appletalk = 12,
      AF_DecnetIV = 13,
      AF_BanyanVines = 14,
      AF_E164N = 15 // with NSAP format subaddress
    };

    enum LocalMembership
    {
      Local_NoInfo = 1, Local_Include = 2
    };

/// Downstream Prune, Join, and Graft Messages. The Prune(S,G) Downstream state machine for receiving Prune, Join and
/// Graft messages on interface I is given below.  This state machine MUST always be in the NoInfo state on the upstream interface.
/// It contains three states.
    enum PruneState
    {
      /// NoInfo(NI). The interface has no (S,G) Prune state, and neither the Prune
      /// timer (PT(S,G,I)) nor the PrunePending timer ((PPT(S,G,I)) is running.
      Prune_NoInfo,

      /// PrunePending(PP). The router has received a Prune(S,G) on this interface from a
      /// downstream neighbor and is waiting to see whether the prune will be overridden
      /// by another downstream router.  For forwarding purposes,
      /// the PrunePending state functions exactly like the NoInfo state.
      Prune_Pruned,

      /// Pruned(P). The router has received a Prune(S,G) on this interface from a
      /// downstream neighbor, and the Prune was not overridden.  Data from
      /// S addressed to group G is no longer being forwarded on this interface.
      Prune_PrunePending
    };

/// (S,G) Assert State Machine.
/// The (S,G) Assert state machine for interface I is shown in Figure 4. There are three states:
    enum AssertWinnerState
    {
      ///  This router has no (S,G) Assert state on interface I.
      Assert_NoInfo,

      /// This router has won an (S,G) Assert on interface I.  It is now responsible for forwarding traffic from S destined for G via interface I.
      /// An Assert loser that receives a Prune(S,G), Join(S,G), or Graft(S,G) directed to it initiates a new Assert negotiation so
      ///	   that the downstream router can correct its RPF'(S).

      Assert_Loser,

      /// This router has lost an (S,G) Assert on interface I.  It must not forward packets from S destined for G onto interface I.
      /// The Assert winner for (S,G) must act as the local forwarder for (S,G) on behalf of all downstream members.
      Assert_Winner
    };

///  Upstream interface-specific:
    enum GraftPruneState
    {
      GP_NoInfo,

      /// The set, olist(S,G), is empty.  The router will not forward data
      /// from S addressed to group G.
      GP_Pruned,

      /// This is the starting state of the Upsteam(S,G) state machine.
      /// The state machine is in this state if it just started or if olist(S,G) != NULL.
      GP_Forwarding,

      /// The router was in the Pruned(P) state, but a transition has
      /// occurred in the Downstream(S,G) state machine for one of this
      /// (S,G) entry's outgoing interfaces, indicating that traffic from S
      /// addressed to G should again be forwarded.  A Graft message has
      /// been sent to RPF'(S), but a Graft Ack message has not yet been received.
      GP_AckPending
    };

    enum Origination
    {
///NotOriginator(NO). This is the starting state of the Origination(S,G) state machine.
///	While in this state, a router will not originate State Refresh messages for the (S,G) pair.
      NotOriginator,
///Originator(O). When in this state the router will periodically originate State
///	Refresh messages.  Only routers directly connected to S may transition to this state.
      Originator,
    };
  }
}
#endif
