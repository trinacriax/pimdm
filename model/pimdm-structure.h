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
#include <set>
#include <iostream>
#include <stdio.h>
#include "ns3/ipv4-address.h"
#include "ns3/pimdm-packet.h"
#include "ns3/nstime.h"
#include "ns3/timer.h"

namespace ns3 {
namespace pimdm {
# define MaxGraftRetry 6

struct AssertMetric {
	AssertMetric():
		metricPreference(0),
		routeMetric(0),
		IPAddress("0.0.0.0")
	{}
	AssertMetric(int m, int r, uint32_t ip):
		metricPreference(m),
		routeMetric(r),
		IPAddress(ip)
	{}
	AssertMetric(int m, int r, Ipv4Address ip):
		metricPreference(m),
		routeMetric(r),
		IPAddress(ip)
	{}
    uint32_t metricPreference;
    uint32_t routeMetric;
    Ipv4Address IPAddress;
   };

static inline bool
operator == (const AssertMetric &a, const AssertMetric &b){
	return (a.metricPreference == b.metricPreference) &&
			(a.routeMetric == b.routeMetric);
}

static inline std::ostream&
operator << (std::ostream& o, const AssertMetric &a){
	return o << a.metricPreference << " "<< a.routeMetric<<" "<< a.IPAddress;
}

//When assert_metrics are compared, the metricPreference and routeMetric field are compared in order,
//	where the first lower value wins.  If all fields are equal, the IP address of the router that
//  sourced the Assert message is used as a tie-breaker, with the highest IP address winning.
static inline bool
operator > (const AssertMetric &a, const AssertMetric &b){
	bool result = (a.metricPreference < b.metricPreference);
	result = result || ((a.metricPreference == b.metricPreference) && (a.routeMetric < b.routeMetric));
	result = result || ((a.metricPreference == b.metricPreference) && (a.routeMetric == b.routeMetric) && (a.IPAddress != b.IPAddress) && !(a.IPAddress < b.IPAddress));
	return result;
}

static inline bool
operator < (const AssertMetric &a, const AssertMetric &b){
	return b > a;
}

/// (S,G) Pair. Source S and destination group G associated with an IP packet.
struct SourceGroupPair{
	SourceGroupPair():
		sourceMulticastAddr("0.0.0.0"),
		groupMulticastAddr("0.0.0.0"),
		nextMulticastAddr("0.0.0.0")
	{}
	SourceGroupPair(Ipv4Address s, Ipv4Address g):
		sourceMulticastAddr(s),
		groupMulticastAddr(g){nextMulticastAddr = Ipv4Address::GetAny();}
	SourceGroupPair(Ipv4Address s, Ipv4Address g, Ipv4Address n):
			sourceMulticastAddr(s),
			groupMulticastAddr(g),
			nextMulticastAddr(n){}
  /// Interface address of the source.
	Ipv4Address sourceMulticastAddr;
  /// Multicast group address.
	Ipv4Address groupMulticastAddr;
  /// Next hop address.
	Ipv4Address nextMulticastAddr;
};

static inline bool
operator == (const SourceGroupPair &a, const SourceGroupPair &b){
	return (a.sourceMulticastAddr == b.sourceMulticastAddr)&&
			(a.groupMulticastAddr == b.groupMulticastAddr);
}

static inline bool
operator < (const SourceGroupPair &a, const SourceGroupPair &b){
	return (a.groupMulticastAddr < b.groupMulticastAddr) ||
			((a.groupMulticastAddr == b.groupMulticastAddr) && (a.sourceMulticastAddr < b.sourceMulticastAddr));
}

static inline std::ostream&
operator << (std::ostream &os, const SourceGroupPair &a){
	os << "SourceGroupPair(SourceAddress = "<< a.sourceMulticastAddr<< ", GroupAddress = " << a.groupMulticastAddr<<")";
	return os;
}

struct SourceGroupState{
	SourceGroupState(SourceGroupPair sgp):
		SGPair(sgp),
		LocalMembership(Local_NoInfo),
		AssertState(Assert_NoInfo),
		AssertWinner(),
		SG_AT(Timer::CANCEL_ON_DESTROY),
		PruneState(Prune_NoInfo),
		SG_PT(Timer::CANCEL_ON_DESTROY),
		SG_PPT(Timer::CANCEL_ON_DESTROY),
		lastStateRefresh(Seconds(0)),
		SGAM(0),
		SG_SR_TTL(0),
		SG_DATA_TTL(0)
	{upstream = NULL;}
	~SourceGroupState(){}

	/// SourceGroup pair.
	struct SourceGroupPair SGPair;
	/// Local membership.
	enum LocalMembership LocalMembership;///<4.1.2. State: One of {"NoInfo", "Include"}
	/// Assert Winner State.
	enum AssertWinnerState AssertState;///4.1.2. State: One of {"NoInfo" (NI), "I lost Assert" (L), "I won Assert" (W)}
	/// Assert Winner on (S,G,I)
	struct AssertMetric AssertWinner;
	/// Assert Timer.
	Timer SG_AT;
	/// Prune State.
	enum PruneState PruneState;///<4.1.2. State: One of {"NoInfo" (NI), "Pruned" (P), "PrunePending" (PP)}
	/// Prune Timer (PT(S,G,I)). This timer is set when the PrunePending Timer (PT(S,G,I))
    /// expires.  Expiry of the Prune Timer (PT(S,G,I)) causes the
    /// interface to transition to the NoInfo (NI) state, thereby
    /// allowing data from S addressed to group G to be forwarded on the interface.
	Timer SG_PT;/// Prune Timer (PT)
	/// PrunePending Timer (PPT(S,G,I))
	/// This timer is set when a valid Prune(S,G) is received. Expiry of
	/// the PrunePending Timer (PPT(S,G,I)) causes the interface to
	/// transition to the Pruned state.
	Timer SG_PPT;/// Prune Pending Timer (PPT)
	/// Pointer to upstream data
	struct UpstreamState *upstream;
	/// Time of the last received StateRefresh(S,G)
	Time lastStateRefresh;
	/// Assert winner's Assert Metric.
	uint32_t SGAM;
	/// TTL of the packet to use in State Refresh messages.
	uint8_t SG_SR_TTL;
	/// TTL of the packet to use in Data packets.
	uint8_t SG_DATA_TTL;
};

static inline bool
operator == (const SourceGroupState &a, const SourceGroupState &b){
	return (a.SGPair == b.SGPair);
}

struct UpstreamState{
	UpstreamState():
		GraftPrune(GP_Forwarding),
		SG_GRT(Timer::CANCEL_ON_DESTROY),
		SG_OT(Timer::CANCEL_ON_DESTROY),
		SG_PLT(Timer::CANCEL_ON_DESTROY),
		SG_SAT(Timer::CANCEL_ON_DESTROY),
		SG_SRT(Timer::CANCEL_ON_DESTROY),
		origination(NotOriginator)
	{}
	~UpstreamState(){}

	///< Upstream interface-specific:
	/// Graft/Prune State.
	enum GraftPruneState GraftPrune;///< 4.1.2. State: One of {"NoInfo" (NI), "Pruned" (P), "Forwarding" (F),"AckPending" (AP) }
	/// GraftRetry Timer (GRT). This timer is set when a Graft is sent upstream.  If a corresponding GraftAck
	///  is not received before the timer expires, then another Graft is sent, and the GraftRetry Timer is reset.
	///  The timer is stopped when a Graft Ack message is received.  This timer is normally set to Graft_Retry_Period (see 4.8).
	Timer SG_GRT;
	/// Upstream Override Timer (OT). This timer is set when a Prune(S,G) is received on the upstream
	/// interface where olist(S,G) != NULL.  When the timer expires, a Join(S,G) message
	/// is sent on the upstream interface.  This timer is normally set to t_override (see 4.8).
	Timer SG_OT;
	/// Prune Limit Timer (PLT). This timer is used to rate-limit Prunes on a LAN.  It is only
	/// used when the Upstream(S,G) state machine is in the Pruned state.
	/// A Prune cannot be sent if this timer is running.
	/// This timer is normally set to t_limit (see 4.8).
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
	/// Pointer to Origination(S,G) machine
	enum Origination origination;///<4.1.2.
};

//static inline std::ostream&
//operator << (std::ostream &os, const SourceGroupState &a){
//	os << "SourceGroupState (SourceGroupPair = ("<< a.SGPair.sourceMulticastAddr <<
//			","<<a.SGPair.groupMulticastAddr<< "), LocalMembership = " << a.LocalMembership <<
//			", PruneState = " << a.PruneState << ", PPT = " << a.SGPPT.GetDelay().GetSeconds() <<
//			", PT = "<< a.SGPT << ", Assert Winner = " << a.AssertState <<
//			", Assert Timer = "<< a.SGAT << ", Assert winner IP = "<< a.SGAW <<
//			", Assert winner Metric = "<<a.SGAM<<", Graft/Prune State = " <<
//			", GraftPruneState = "<<a.GraftPrune<< ", GRT = "<< a.SGGRT.GetDelay().GetSeconds() <<
//			", OT = " << a.SGOT << ", SGPLT = "<< a.SGSAT << ", SGSRT = "<< a.SGSRT<<");";
//	return os;
//}

typedef std::list<SourceGroupState> SourceGroupList;	///< SourceGroup List.

	struct NeighborState {//one for each neighbor
//		NeighborState():
//			neighborIfaceAddr("0.0.0.0"),
//			receivingIfaceAddr("0.0.0.0"),
//			neighborCreation(Seconds(0)),
//			neighborRefresh(Seconds(0)),
//			neighborTimeout(Seconds(0)),
//			neighborTimeoutB(false),
//			neigborNLT(Timer::CANCEL_ON_DESTROY),
//			neighborHoldTime(Seconds(0)),
//			neighborT(0),
//			neighborPropagationDelay(Seconds(0)),
//			neighborOverrideInterval(Seconds(0)),
//			neighborGenerationID(0),
//			neighborVersion(0),
//			neighborInterval(RefreshInterval)
//		{
//			neighborGraftRetry[0] = 0;
//			neighborGraftRetry[1] = MaxGraftRetry;
//		}
		NeighborState(Ipv4Address neighbor, Ipv4Address rec):
			neighborIfaceAddr(neighbor),
			receivingIfaceAddr(rec),
			neighborCreation(Seconds(0)),
			neighborRefresh(Seconds(0)),
			neighborTimeout(Seconds(0)),
			neighborTimeoutB(false),
			neigborNLT(Timer::CANCEL_ON_DESTROY),
			neighborHoldTime(Seconds(0)),
			neighborT(0),
			neighborPropagationDelay(Seconds(0)),
			neighborOverrideInterval(Seconds(0)),
			neighborGenerationID(0),
			neighborVersion(0),
			neighborInterval(RefreshInterval)
		{
			neighborGraftRetry[0] = 0;
			neighborGraftRetry[1] = MaxGraftRetry;
		}
		~NeighborState(){}

		/// Interface address of the neighbor node.
		Ipv4Address neighborIfaceAddr;
		/// Interface address of the local node to the neighbor
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
//		/// State Refresh Capable reserved all zero.
//		uint16_t neighborReserved;
		/// Graft retries.
		uint8_t neighborGraftRetry[2];
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
			", HoldTime = " << a.neighborHoldTime.GetSeconds() << ", Timeout ="<<a.neighborTimeout.GetSeconds()<<
			", NLT = "<<a.neigborNLT.GetDelay()<< ")";
	return os;
}

typedef std::list<NeighborState> NeighborList;	///< Neighbor List.

struct NeighborhoodStatus{
	NeighborhoodStatus():
		stateRefreshCapable(false),
		LANDelayEnabled(false),
		hello_timer(Timer::CANCEL_ON_DESTROY),
		propagationDelay(Seconds(Propagation_Delay)),
		overrideInterval(Seconds(Override_Interval)),
		stateRefreshInterval(Seconds(RefreshInterval)),
		pruneHoldtime(Seconds(PruneHoldTime))
		{neighbors.clear();}
	bool stateRefreshCapable; ///< State refresh capability.
	bool LANDelayEnabled; ///< LAN Delay Enabled.
	Timer hello_timer;///< Hello Timer (HT) (RFC 3973, section 4.1.1).
	Time propagationDelay; ///< Propagation delay.
	Time overrideInterval; ///< Override Interval field is a time interval in units of milliseconds.
	Time stateRefreshInterval;///< Router's configured state refresh
	Time pruneHoldtime;
	NeighborList neighbors; ///< Neighbor State
	~NeighborhoodStatus(){}
};

typedef std::pair<int32_t, Ipv4Address> WiredEquivalentInterface ;	///< Neighbor List.

/*** IGMP LIKE ***/
#define IGMP_RENEW 5

enum PeerRole {
	CLIENT,
	ROUTER
};

struct SGState{
	/// SourceGroup pair.
	SourceGroupPair sgsPair;
	/// Source-Group Renew Timer.
	Timer sgsRenew;
	/// Active interface for such source-group;
	std::set<int32_t> sgsInterfaces;

	SGState(SourceGroupPair sgp):
		sgsPair(sgp),
		sgsRenew(Timer::CANCEL_ON_DESTROY)
	{sgsInterfaces.clear();}
	~SGState(){
//		sgsInterfaces.clear();
	}


};

static inline bool
operator == (const SGState &a, const SGState &b){
	return (a.sgsPair == b.sgsPair);
}
/*** IGMP LIKE ***/

}}; // namespace ns3, pimdm

#endif  /* __PIM_DM_STRUCTURE_H__ */
