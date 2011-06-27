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

///
/// \file	pimdm-structure.h
/// \brief	This file contains all the data structures used by a PIM-DM node.
///

#ifndef __PIM_DM_STRUCTURE_H__
#define __PIM_DM_STRUCTURE_H__

#include <list>
#include <iostream>
#include <stdio.h>
#include "ns3/ipv4-address.h"
#include "ns3/pimdm-packet.h"
#include "ns3/nstime.h"
#include "ns3/timer.h"

namespace ns3 {
namespace pimdm {

struct AssertMetric {
     uint32_t metric_preference;
     uint32_t route_metric;
     Ipv4Address ip_address;
   };

static inline bool
operator == (const AssertMetric &a, const AssertMetric &b){
	return (a.metric_preference == b.metric_preference) &&
			(a.route_metric == b.route_metric);
}
static inline bool
operator > (const AssertMetric &a, const AssertMetric &b){
	return (a.metric_preference < b.metric_preference) ||
			((a.metric_preference == b.metric_preference) && (a.route_metric < b.route_metric))||
			((a.metric_preference == b.metric_preference) && (a.route_metric == b.route_metric) &&
					a.ip_address<b.ip_address);
}

/// (S,G) Pair. Source S and destination group G associated with an IP packet.
struct SourceGroupPair
{
  /// Interface address of the source.
	Ipv4Address sourceIfaceAddr;
  /// Multicast group address.
	Ipv4Address groupMulticastAddr;
};

static inline bool
operator == (const SourceGroupPair &a, const SourceGroupPair &b){
	return (a.sourceIfaceAddr == b.sourceIfaceAddr)&&
			(a.groupMulticastAddr == b.groupMulticastAddr);
}

static inline std::ostream&
operator << (std::ostream &os, const SourceGroupPair &a){
	os << "SourceGroupPair( SourceAddress = "<< a.sourceIfaceAddr<< ", GroupAddress = " << a.groupMulticastAddr<<")";
	return os;
}

struct SourceGroupState{
	/// SourceGroup pair.
	struct SourceGroupPair SGPair;

	/// local members on interface I that seek to receive all traffic sent to G.
	bool members;

	/// Time of the last received StateRefresh(S,G)
	Time lastStateRefresh;

	/// Local membership.
	enum LocalMembership SGLocalMembership;

	/// Assert Winner State.
	enum AssertWinnerState SGAssertState;

	/// Assert Winner on (S,G,I)
	struct AssertMetric SGAssertWinner;

	/// Assert Timer.
	Timer SG_AT;

	/// Prune State.
	enum PruneState SGPruneState;

	/// Prune Timer (PT(S,G,I)). This timer is set when the PrunePending Timer (PT(S,G,I))
    /// expires.  Expiry of the Prune Timer (PT(S,G,I)) causes the
    /// interface to transition to the NoInfo (NI) state, thereby
    /// allowing data from S addressed to group G to be forwarded on the interface.
	Timer SG_PT;

	/// PrunePending Timer (PPT(S,G,I))
	/// This timer is set when a valid Prune(S,G) is received. Expiry of
	/// the PrunePending Timer (PPT(S,G,I)) causes the interface to
	/// transition to the Pruned state.
	Timer SG_PPT;

	/// Assert winner's IP Address.
	Ipv4Address SGAW;

	/// Assert winner's Assert Metric.
	uint32_t SGAM;

	/// TTL of the packet for use in State Refresh messages.
	uint8_t SG_SR_TTL;
	uint8_t SG_DATA_TTL;
	/// Pointer to upstream data
	struct UpstreamState *upstream;
	/// Pointer to Origination(S,G) machine
	enum Origination origination;
};

static inline bool
operator == (const SourceGroupState &a, const SourceGroupState &b){
	return (a.SGPair == b.SGPair);
}

struct UpstreamState{
	///< Upstream interface-specific:
	/// Graft/Prune State.
	enum GraftPruneState SGGraftPrune;

	/// GraftRetry Timer (GRT). This timer is set when a Graft is sent upstream.  If a corresponding GraftAck
	///  is not received before the timer expires, then another Graft is sent, and the GraftRetry Timer is reset.
	///  The timer is stopped when a Graft Ack message is received.  This timer is normally set to Graft_Retry_Period (see 4.8).
	Timer SG_GRT;

	/// Upstream Override Timer (OT). This timer is set when a Prune(S,G) is received on the upstream
	/// interface where olist(S,G) != NULL.  When the timer expires, a Join(S,G) message
	/// is sent on the upstream interface.  This timer is normally set to t_override (see 4.8).
	Timer SG_OT;

	/// Prune Limit Timer (PLT). This timer is used to rate-limit Prunes on a LAN.  It is only
	/// used when the Upstream(S,G) state machine is in the Pruned state. A Prune cannot be sent if this timer is running.  This timer is
	/// normally set to t_limit (see 4.8).
	Timer SG_PLT;

	//Originator State: Source Active Timer (SAT).
	//	This timer is first set when the Origination(S,G) state machine
	//	transitions to the O state and is reset on the receipt of every
	//	data packet from S addressed to group G.  When it expires, the
	//	Origination(S,G) state machine transitions to the NO state.
	//	This timer is normally set to SourceLifetime (see 4.8).
	Timer SG_SAT;

	/// Originator State: State Refresh Timer (SRT).
	//    This timer controls when State Refresh messages are generated.
	//	  The timer is initially set when that Origination(S,G) state machine transitions to the O state.
	//	  It is cancelled when the Origination(S,G) state machine transitions to the NO state.
	//	  This timer is normally set to StateRefreshInterval (see 4.8).
	Timer SG_SRT;
};

//static inline std::ostream&
//operator << (std::ostream &os, const SourceGroupState &a){
//	os << "SourceGroupState (SourceGroupPair = ("<< a.SGPair.sourceIfaceAddr <<
//			","<<a.SGPair.groupMulticastAddr<< "), LocalMembership = " << a.SGLocalMembership <<
//			", PruneState = " << a.SGPruneState << ", PPT = " << a.SGPPT.GetDelay().GetSeconds() <<
//			", PT = "<< a.SGPT << ", Assert Winner = " << a.SGAssertState <<
//			", Assert Timer = "<< a.SGAT << ", Assert winner IP = "<< a.SGAW <<
//			", Assert winner Metric = "<<a.SGAM<<", Graft/Prune State = " <<
//			", GraftPruneState = "<<a.SGGraftPrune<< ", GRT = "<< a.SGGRT.GetDelay().GetSeconds() <<
//			", OT = " << a.SGOT << ", SGPLT = "<< a.SGSAT << ", SGSRT = "<< a.SGSRT<<");";
//	return os;
//}



typedef std::list<SourceGroupState> SourceGroupList;	///< SourceGroup List.

	struct NeighborState {//one for each neighbor
		/// Interface address of the neighbor node.
		Ipv4Address neighborIfaceAddr;
		/// Interface address of the local node to the neighbor.
		Ipv4Address receivingIfaceAddr;
		/// Creation time of the current neighbor.
		Time neighborCreation;
		/// Time of last refresh.
		Time neighborRefresh;
		/// Time the entry is expired.
		Time neighborTimeout;
		/// Timeout is enabled
		bool neighborTimeoutB;

		/// * * * Hello Information * * *
		/// Neighbor Liveness Timer: NLT(N,I)
		Timer neigborNLT;
		/// Time to keep the information.
		Time neighborHoldTime;
		/// LAN prune delay T bit 0 in DM.
		uint8_t neighborT;
		/// LAN prune delay propagation time interval in milliseconds.
		Time neighborPropagationDelay;
		/// LAN prune delay override time interval in milliseconds.
		Time neighborOverrideInterval;
		/// Generation ID random value for the interface.
		uint32_t neighborGenerationID;
		/// State Refresh Capable version.
		uint8_t neighborVersion;
		/// State Refresh Capable interval in seconds.
		uint8_t neighborInterval;
		/// State Refresh Capable reserved all zero.
		uint16_t neighborReserved;
	};

static inline bool
operator == (const NeighborState &a, const NeighborState &b){
	return (a.neighborIfaceAddr == b.neighborIfaceAddr)&&
			(a.receivingIfaceAddr == b.receivingIfaceAddr);
}

static inline bool
operator < (const NeighborState &a, const NeighborState &b){
	return (a.neighborIfaceAddr < b.neighborIfaceAddr);
}

static inline std::ostream&
operator << (std::ostream &os, const NeighborState &a){
	os << "NeighborState( neighborIface = "<< a.neighborIfaceAddr<< ", receivingIface = " << a.receivingIfaceAddr<<
			", Creation = " << a.neighborCreation.GetSeconds() <<", Refresh = "<<a.neighborRefresh.GetSeconds()<<
			", HoldTime = " << a.neighborHoldTime.GetSeconds() << ", Timeout ="<<a.neighborTimeout.GetSeconds()<<")";
	return os;
}

typedef std::list<NeighborState> NeighborList;	///< Neighbor List.

struct NeighborhoodStatus{
	bool stateRefreshCapable; ///< State refresh capability.
	bool LANDelayEnabled; ///< LAN Delay Enabled.
	Time propagationDelay; ///< Propagation delay.
	Time overrideInterval; ///< Override Interval field is a time interval in units of milliseconds.
	Time stateRefreshInterval;///< Router's configured state refresh
	Time pruneHoldtime;
	NeighborList neighbors; ///< Neighbor State
};

}}; // namespace ns3, pimdm

#endif  /* __PIM_DM_STRUCTURE_H__ */
