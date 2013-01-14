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

namespace ns3
{
  namespace pimdm
  {

    const uint32_t MaxGraftRetry = 6;
/// Time default value for RPF check.
    const uint32_t RPF_CHECK = 10;
/// Timer Name: Hello Timer (HT). Periodic interval for hello messages.
    const uint32_t Hello_Period = 30;
/// Timer Name: Hello Timer (HT). Random interval for initial Hello message on bootup or triggered Hello message to a rebooting neighbor.
    const uint32_t Triggered_Hello_Delay = 5;
    /**
     *
     * The Hold Time in the Hello Message should be set to a value that can
     * reasonably be expected to keep the Hello active until a new Hello
     * message is received. On most links, this will be 3.5 times the value
     * of Hello_Period.
     *
     */
    const uint16_t Hold_Time_Default = ((uint16_t) (3.5 * Hello_Period)); //seconds
/// Timer Name: Assert Timer (AT (S,G,I)). Period after last assert before assert state is timed out.
    const uint32_t Assert_Time = 180;
/// Timer Name: Graft Retry Timer (GRT (S,G)). In the absence of receipt of a GraftAck message, the time before retransmission of a Graft message.
    const uint32_t Graft_Retry_Period = 3;
/// Used to prevent Prune storms on a LAN.
    const uint32_t t_limit = 10; //210 in LAN
    const uint32_t t_shorter = 2;
    /**
     * Timer Name: Source Active Timer (SAT (S,G)).
     * Period of time after receiving a multicast message a directly
     * attached router will continue to send State Refresh messages.
     */
    const uint32_t SourceLifetime = 210;
/// Timer Name: State Refresh Timer (SRT (S,G)). Interval between successive state refresh messages.
    const uint32_t RefreshInterval = 60;
    const uint32_t StateRefreshInterval = RefreshInterval;
    /**
     *  If all routers on a LAN are using the LAN Prune Delay option, the Override_Interval (OI (I)) MUST be set to the
     *  largest value on the LAN. Otherwise, the Override_Interval (OI (I)) MUST be set to 2.5 seconds.
     */
    const double Override_Interval = 2.5;
    /**
     * The J/P_Override_Interval is the sum of the interface's
     * Override_Interval (OI (I)) and Propagation_Delay (PD (I)). If all
     * routers on a LAN are using the LAN Prune Delay option, both
     * parameters MUST be set to the largest value on the LAN. Otherwise,
     * the Override_Interval (OI (I)) MUST be set to 2.5 seconds, and the
     * Propagation_Delay (PD (I)) MUST be set to 0.5 seconds.
     *
     */
    const double Propagation_Delay = 0.5;
    /**
     * The number of seconds a receiving PIM-DM router MUST keep a Prune
     * state alive, unless removed by a Join or Graft message. If the
     * Hold Time is '0xffff', the receiver MUST NOT remove the Prune state
     * unless a corresponding Join or Graft message is received. The Hold
     * Time is ignored in Join messages.
     */
    const uint32_t PruneHoldTime = 0xffff;
    /**
     * If all routers on a LAN support the LAN Prune Delay option, then the
     * PIM routers on that LAN will use the values received to adjust their
     * J/P_Override_Interval on that interface and the interface is LAN
     * Delay Enabled. Briefly, to avoid synchronization of Prune Override
     * (Join) messages when multiple downstream routers share a multi-access
     * link, sending of these messages is delayed by a small random amount
     * of time. The period of randomization is configurable and has a
     * default value of 3 seconds.
     */
    const uint32_t JoinDelay = 3; //Prune override
    /**
     * Prune downstream to limit the number of prune message sent in downstream
     * because of the broadcast nature of the wireless channel.
     */
    const uint32_t PRUNE_DOWN = 4;

    struct AssertMetric
    {
        AssertMetric () :
            metricPreference(0), routeMetric(0), IPAddress("0.0.0.0")
        {
        }
        AssertMetric (int m, int r, uint32_t ip) :
            metricPreference(m), routeMetric(r), IPAddress(ip)
        {
        }
        AssertMetric (int m, int r, Ipv4Address ip) :
            metricPreference(m), routeMetric(r), IPAddress(ip)
        {
        }
        uint32_t metricPreference;
        uint32_t routeMetric;
        Ipv4Address IPAddress;
    };

    static inline bool
    operator == (const AssertMetric &a, const AssertMetric &b)
    {
      return (a.metricPreference == b.metricPreference) && (a.routeMetric == b.routeMetric);
    }

    static inline std::ostream&
    operator << (std::ostream& o, const AssertMetric &a)
    {
      return o << a.metricPreference << " " << a.routeMetric << " " << a.IPAddress;
    }

//When assert_metrics are compared, the metricPreference and routeMetric field are compared in order,
//	where the first lower value wins.  If all fields are equal, the IP address of the router that
//  sourced the Assert message is used as a tie-breaker, with the highest IP address winning.
    static inline bool
    operator > (const AssertMetric &a, const AssertMetric &b)
    {
      bool result = (a.metricPreference < b.metricPreference);
      result = result || ((a.metricPreference == b.metricPreference) && (a.routeMetric < b.routeMetric));
      result = result
          || ((a.metricPreference == b.metricPreference) && (a.routeMetric == b.routeMetric)
              && (a.IPAddress != b.IPAddress) && !(a.IPAddress < b.IPAddress));
      return result;
    }
//
//static inline bool
//operator < (const AssertMetric &a, const AssertMetric &b){
//	bool result = (a.metricPreference > b.metricPreference);
//	result = result || ((a.metricPreference == b.metricPreference) && (a.routeMetric > b.routeMetric));
//	result = result || ((a.metricPreference == b.metricPreference) && (a.routeMetric == b.routeMetric) && (a.IPAddress != b.IPAddress) && !(a.IPAddress > b.IPAddress));
//	return result;
//}

/// (S,G) Pair. Source S and destination group G associated with an IP packet.
    struct SourceGroupPair
    {
        SourceGroupPair () :
            sourceMulticastAddr("0.0.0.0"), groupMulticastAddr("0.0.0.0"), nextMulticastAddr("0.0.0.0")
        {
        }
        SourceGroupPair (Ipv4Address s, Ipv4Address g) :
            sourceMulticastAddr(s), groupMulticastAddr(g)
        {
          nextMulticastAddr = Ipv4Address::GetAny();
        }
        SourceGroupPair (Ipv4Address s, Ipv4Address g, Ipv4Address n) :
            sourceMulticastAddr(s), groupMulticastAddr(g), nextMulticastAddr(n)
        {
        }
        /// Interface address of the source.
        Ipv4Address sourceMulticastAddr;
        /// Multicast group address.
        Ipv4Address groupMulticastAddr;
        /// Next hop address.
        Ipv4Address nextMulticastAddr;
    };

    static inline bool
    operator == (const SourceGroupPair &a, const SourceGroupPair &b)
    {
      return (a.sourceMulticastAddr == b.sourceMulticastAddr) && (a.groupMulticastAddr == b.groupMulticastAddr);
    }

    static inline bool
    operator < (const SourceGroupPair &a, const SourceGroupPair &b)
    {
      return (a.groupMulticastAddr < b.groupMulticastAddr)
          || ((a.groupMulticastAddr == b.groupMulticastAddr) && (a.sourceMulticastAddr < b.sourceMulticastAddr));
    }

    static inline std::ostream&
    operator << (std::ostream &os, const SourceGroupPair &a)
    {
      os << "SourceGroupPair(SourceAddress = " << a.sourceMulticastAddr << ", GroupAddress = " << a.groupMulticastAddr
          << ")";
      return os;
    }

    struct UpstreamState
    {
        UpstreamState () :
            GraftPrune(GP_Forwarding), SG_GRT(Timer::CANCEL_ON_DESTROY), SG_OT(Timer::CANCEL_ON_DESTROY),
            SG_PLT(Timer::CANCEL_ON_DESTROY), SG_SAT(Timer::CANCEL_ON_DESTROY), SG_SRT(Timer::CANCEL_ON_DESTROY),
            origination(NotOriginator), valid(false)
        {
        }
        UpstreamState (bool valid) :
            GraftPrune(GP_Forwarding), SG_GRT(Timer::CANCEL_ON_DESTROY), SG_OT(Timer::CANCEL_ON_DESTROY),
            SG_PLT(Timer::CANCEL_ON_DESTROY), SG_SAT(Timer::CANCEL_ON_DESTROY), SG_SRT(Timer::CANCEL_ON_DESTROY),
            origination(NotOriginator), valid(valid)
        {
        }
        ~UpstreamState ()
        {
        }

        /**
         * Upstream interface-specific: Graft/Prune State.
         */
        enum GraftPruneState GraftPrune; ///< 4.1.2. State: One of {"NoInfo" (NI), "Pruned" (P), "Forwarding" (F),"AckPending" (AP) }
        /** GraftRetry Timer (GRT). This timer is set when a Graft is sent upstream.
         * If a corresponding GraftAck is not received before the timer expires, then another Graft is sent, and the GraftRetry Timer is reset.
         * The timer is stopped when a Graft Ack message is received.  This timer is normally set to Graft_Retry_Period (see 4.8).
         */
        Timer SG_GRT;
        /**
         * Upstream Override Timer (OT). This timer is set when a Prune(S,G) is received on the upstream
         * interface where olist(S,G) != NULL.  When the timer expires, a Join(S,G) message
         * is sent on the upstream interface.  This timer is normally set to t_override (see 4.8).
         */
        Timer SG_OT;
        /**
         * Prune Limit Timer (PLT). This timer is used to rate-limit Prunes on a LAN.  It is only
         * used when the Upstream(S,G) state machine is in the Pruned state.
         * A Prune cannot be sent if this timer is running.
         * This timer is normally set to t_limit (see 4.8).
         */
        Timer SG_PLT;
        /**
         * Originator State: Source Active Timer (SAT).
         * This timer is first set when the Origination(S,G) state machine
         * transitions to the O state and is reset on the receipt of every
         * data packet from S addressed to group G.  When it expires, the
         * Origination(S,G) state machine transitions to the NO state.
         * This timer is normally set to SourceLifetime (see 4.8).
         */
        Timer SG_SAT;
        /**
         * Originator State: State Refresh Timer (SRT).
         * This timer controls when State Refresh messages are generated.
         * The timer is initially set when that Origination(S,G) state machine transitions to the O state.
         * It is cancelled when the Origination(S,G) state machine transitions to the NO state.
         * This timer is normally set to StateRefreshInterval (see 4.8).
         */
        Timer SG_SRT;
        /// Pointer to Origination(S,G) machine
        enum Origination origination; ///<4.1.2.
        /// bool
        bool valid;
    };

    struct SourceGroupState
    {
        SourceGroupState (SourceGroupPair sgp) :
            SGPair(sgp), LocalMembership(Local_NoInfo), AssertState(Assert_NoInfo), AssertWinner(),
            SG_AT(Timer::CANCEL_ON_DESTROY), PruneState(Prune_NoInfo), SG_PT(Timer::CANCEL_ON_DESTROY),
            SG_PPT(Timer::CANCEL_ON_DESTROY), SG_PLTD(Timer::CANCEL_ON_DESTROY), upstream(false),
            lastStateRefresh(Seconds(0)), SGAM(0), SG_SR_TTL(0), SG_DATA_TTL(0)
        {
        }

        ~SourceGroupState ()
        {
        }

        /// SourceGroup pair.
        struct SourceGroupPair SGPair;
        /// Local membership.
        enum LocalMembership LocalMembership;	///<4.1.2. State: One of {"NoInfo", "Include"}
        /// Assert Winner State.
        enum AssertWinnerState AssertState;	///4.1.2. State: One of {"NoInfo" (NI), "I lost Assert" (L), "I won Assert" (W)}
        /// Assert Winner on (S,G,I)
        struct AssertMetric AssertWinner;
        /// Assert Timer.
        Timer SG_AT;
        /// Prune State.
        enum PruneState PruneState;	///<4.1.2. State: One of {"NoInfo" (NI), "Pruned" (P), "PrunePending" (PP)}
        /**
         * Prune Timer (PT(S,G,I)). This timer is set when the PrunePending Timer (PT(S,G,I)) expires.
         * Expire of the Prune Timer (PT(S,G,I)) causes the
         * interface to transition to the NoInfo (NI) state, thereby
         * allowing data from S addressed to group G to be forwarded on the interface.
         */
        Timer SG_PT;	/// Prune Timer (PT)
        /**
         * PrunePending Timer (PPT(S,G,I))
         * This timer is set when a valid Prune(S,G) is received. Expiry of
         * the PrunePending Timer (PPT(S,G,I)) causes the interface to
         * transition to the Pruned state.
         */
        Timer SG_PPT;	/// Prune Pending Timer (PPT)
        /**
         * Prune Limit Timer (PLT). This timer is used to rate-limit Prunes on a LAN.
         * It is only used when the Downstream(S,G) state machine is in the Pruned state.
         * A Prune cannot be sent if this timer is running.
         * This timer is normally set to t_limit (see 4.8).
         */
        Timer SG_PLTD;
        /// Pointer to upstream data
        struct UpstreamState upstream;
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
    operator == (const SourceGroupState &a, const SourceGroupState &b)
    {
      return (a.SGPair == b.SGPair);
    }

    typedef std::list<SourceGroupState> SourceGroupList;	///< SourceGroup List.

    /**
     * Contains the information about each neighbor.
     */
    struct NeighborState
    {
        NeighborState (Ipv4Address neighbor, Ipv4Address rec) :
            neighborIfaceAddr(neighbor), receivingIfaceAddr(rec), neighborCreation(Seconds(0)),
            neighborRefresh(Seconds(0)), neighborTimeout(Seconds(0)), neighborTimeoutB(false),
            neigborNLT(Timer::CANCEL_ON_DESTROY), neighborHoldTime(Seconds(0)), neighborT(0),
            neighborPropagationDelay(Seconds(0)), neighborOverrideInterval(Seconds(0)), neighborGenerationID(0),
            neighborVersion(0), neighborReserved(0)
        {
          neighborGraftRetry[0] = 0;
          neighborGraftRetry[1] = (uint8_t) MaxGraftRetry;
          neighborInterval = static_cast<uint8_t>(RefreshInterval);
        }
        ~NeighborState ()
        {
        }

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
        /// State Refresh Capable reserved all zero.
        uint16_t neighborReserved;
        /// Graft retries.
        uint8_t neighborGraftRetry[2];
    };

    static inline bool
    operator == (const NeighborState &a, const NeighborState &b)
    {
      return (a.neighborIfaceAddr == b.neighborIfaceAddr) && (a.receivingIfaceAddr == b.receivingIfaceAddr);
    }

    static inline bool
    operator < (const NeighborState &a, const NeighborState &b)
    {
      return (a.neighborIfaceAddr < b.neighborIfaceAddr);
    }

    static inline std::ostream&
    operator << (std::ostream &os, const NeighborState &a)
    {
      os << "NeighborState( neighborIface = " << a.neighborIfaceAddr << ", receivingIface = " << a.receivingIfaceAddr
          << ", Creation = " << a.neighborCreation.GetSeconds() << ", Refresh = " << a.neighborRefresh.GetSeconds()
          << ", HoldTime = " << a.neighborHoldTime.GetSeconds() << ", Timeout =" << a.neighborTimeout.GetSeconds()
          << ", NLT = " << a.neigborNLT.GetDelay() << " DL " << a.neigborNLT.GetDelayLeft() << ")";
      return os;
    }

    typedef std::list<NeighborState> NeighborList;	///< Neighbor List.

    struct NeighborhoodStatus
    {
        NeighborhoodStatus () :
            stateRefreshCapable(false), LANDelayEnabled(false), hello_timer(Timer::CANCEL_ON_DESTROY),
            propagationDelay(Seconds(Propagation_Delay)), overrideInterval(Seconds(Override_Interval)),
            stateRefreshInterval(Seconds(RefreshInterval)), pruneHoldtime(Seconds(PruneHoldTime))
        {
          neighbors.clear();
        }
        bool stateRefreshCapable; ///< State refresh capability.
        bool LANDelayEnabled; ///< LAN Delay Enabled.
        Timer hello_timer; ///< Hello Timer (HT) (RFC 3973, section 4.1.1).
        Time propagationDelay; ///< Propagation delay.
        Time overrideInterval; ///< Override Interval field is a time interval in units of milliseconds.
        Time stateRefreshInterval; ///< Router's configured state refresh
        Time pruneHoldtime; ///< Node's Prune Hold time.
        NeighborList neighbors; ///< Neighbor State
        ~NeighborhoodStatus ()
        {
        }
    };

    typedef std::pair<uint32_t, Ipv4Address> WiredEquivalentInterface;	///< Neighbor List.

  }	// namespace pimdm
}
;
// namespace ns3

#endif  /* __PIM_DM_STRUCTURE_H__ */
