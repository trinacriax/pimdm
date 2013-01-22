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

/// \brief	This header file declares and defines internal state of an PIM-DM node.
#ifndef __PIM_DM_ROUTING_H__
#define __PIM_DM_ROUTING_H__

#include "pimdm-structure.h"
#include "pimdm-packet.h"

#include <ns3/uinteger.h>
#include <ns3/random-variable.h>
#include <ns3/object.h>
#include <ns3/packet.h>
#include <ns3/node.h>
#include <ns3/socket.h>
#include <ns3/event-garbage-collector.h>
#include <ns3/timer.h>
#include <ns3/traced-callback.h>
#include <ns3/ipv4.h>
#include <ns3/ipv4-routing-protocol.h>
#include <ns3/ipv4-static-routing.h>
#include <ns3/ipv4-list-routing.h>
#include <ns3/ipv4-l3-protocol.h>
#include <ns3/string.h>
#include <ns3/aodv-rtable.h>
#include <ns3/aodv-routing-protocol.h>
#include <ns3/mbn-aodv-routing-protocol.h>
#include <ns3/mbn-aodv-common.h>
#include <ns3/olsr-routing-protocol.h>
#include <ns3/dsdv-rtable.h>
#include <ns3/dsdv-routing-protocol.h>
#include <ns3/gnuplot.h>

#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <iterator>

const double TTL_SAMPLE = .2;
const uint32_t PIMDM_TTL = 1;
const uint32_t PIM_RESERVED = 0;
const uint32_t PIM_PORT_NUMBER = 703; //IANA Unassigned
const uint32_t PIM_VERSION_2 = 2;

namespace ns3
{
  namespace pimdm
  {
    struct MulticastEntry
    {
        Ipv4Address sourceAddr; ///< source destination
        Ipv4Address nextAddr; ///< source destination
        uint32_t interface; ///< interface to source
        MulticastEntry () :
            sourceAddr(Ipv4Address::GetAny()), nextAddr(Ipv4Address::GetAny()), interface(0)
        {
        }
        MulticastEntry (Ipv4Address s, Ipv4Address n, uint32_t i) :
            sourceAddr(s), nextAddr(n), interface(i)
        {
        }
    };

    struct RoutingMulticastTable
    {
        Ipv4Address groupAddr; ///< multicast group address
        std::map<Ipv4Address, MulticastEntry> mgroup; ///< source destination
        RoutingMulticastTable () : // default values
            groupAddr(Ipv4Address::GetAny())
        {
        }
        RoutingMulticastTable (Ipv4Address g) : // default values
            groupAddr(g)
        {
        }
    };

/// This class encapsulates all data structures needed for maintaining internal state of an PIM_DM node.
    class MulticastRoutingProtocol : public Ipv4RoutingProtocol
    {
        // friend class;
      private:
        uint32_t m_mainInterface; ///< Node main interface.
        Ipv4Address m_mainAddress; ///< Main address on the main interface.
        uint32_t m_hostInterface; ///< Node main interface.
        Ipv4Address m_hostAddress; ///< Main address on the main interface.

        /// static routing table
        Ptr<Ipv4StaticRouting> m_RoutingTable;

        ///\name Protocol fields;
        //\{
        std::map<uint32_t, NeighborhoodStatus> m_IfaceNeighbors; ///< Information on interface and neighbors (RFC 3973, section 4.1.1).
        ///TIB - Tree Information Base
        std::map<WiredEquivalentInterface, SourceGroupList> m_IfaceSourceGroup; ///< List of (S,G) pair state (RFC 3973, section 4.1.2).

        std::map<SourceGroupPair, std::set<uint32_t> > m_LocalReceiver;

        ///pim ENABLED INTERFACES
        std::map<uint32_t, bool> m_IfacePimEnabled; //TODO, right now all interfaces are pim enabled.
        Time m_helloTime; ///< Hello Time
        uint16_t m_helloHoldTime; ///< Default hello hold time
        uint32_t m_generationID;
        Time m_startTime;
        bool m_stopTx;
        //}
        /// Interface excluded from multicast
        std::set<uint32_t> m_interfaceExclusions;

        ///\name Fields for each interface
        //\{
        Ptr<Ipv4StaticRouting> m_routingTableAssociation;

        /**
         * This is the multicast topology table, which is typically derived
         * from the unicast routing table, or from routing protocols such as
         * MBGP that carry multicast-specific topology information. PIM-DM
         * uses the MRIB to make decisions regarding RPF interfaces.
         */
        std::map<Ipv4Address, RoutingMulticastTable> m_mrib; ///< Multicast Routing Information Base (MRIB)

        /// IP protocol
        Ptr<Ipv4> m_ipv4;
        uint32_t m_identification;
        /// Raw socket per each IP interface, map socket -> iface address (IP + mask)
        std::map<Ptr<Socket>, Ipv4InterfaceAddress> m_socketAddresses;
        /// Pointer to socket
        Ptr<Ipv4RoutingProtocol>* m_routingProtocol;
        /// Loopback device used to defer RREQ until packet will be fully formed
        Ptr<NetDevice> m_lo;
        //}

        Time m_rpfCheck;
        Timer m_rpfChecker;

        Time m_LanDelay;

        EventId eventUpstream;

        Time m_startDelay;

        TracedCallback<Ptr<const Packet> > m_rxControlPacketTrace;
        TracedCallback<Ptr<const Packet> > m_txControlPacketTrace;

        TracedCallback<Ptr<const Packet> > m_rxDataPacketTrace;
        TracedCallback<Ptr<const Packet> > m_txDataPacketTrace;

        TracedCallback<Ptr<const Packet> > m_txControlRouteTrace;
        TracedCallback<uint32_t> m_routingTableChanged;

      protected:
        virtual void
        DoStart (void);

      public:
        static TypeId
        GetTypeId (void);

        MulticastRoutingProtocol ();
        virtual
        ~MulticastRoutingProtocol ();

        uint32_t
        GetMainInterface ();

        void
        SetInterfaceExclusions (std::set<uint32_t> exceptions);
        std::set<uint32_t>
        GetInterfaceExclusions () const;

        /**
         * Return the list of routing table entries discovered by OLSR
         **/
        std::vector<RoutingMulticastTable>
        GetRoutingTableEntries () const;

        void
        registerMember (Ipv4Address source, Ipv4Address group, uint32_t interface);
        void
        unregisterMember (const Ipv4Address source, const Ipv4Address group, const uint32_t interface);
        void
        register_SG (std::string SG);

        void
        UpdateMRIB ();

        /// The cost metric of the unicast route to the source. The metric is in units applicable to the unicast routing protocol used.
        uint16_t
        GetRouteMetric (uint32_t interface, Ipv4Address source);

      private:
        void
        Clear ();
        uint32_t
        GetSize () const;

        void
        RemoveEntry (const Ipv4Address &group);
        void
        RemoveEntry (const Ipv4Address &group, const Ipv4Address &source);
        void
        AddEntry (const Ipv4Address group, const Ipv4Address source, const Ipv4Address next, const uint32_t interface);
        bool
        Lookup (const Ipv4Address group, RoutingMulticastTable &outEntry) const;
        bool
        Lookup (const Ipv4Address group, const Ipv4Address source, RoutingMulticastTable &outEntry,
                MulticastEntry &me) const;
        bool
        UpdateEntry (const Ipv4Address group, const Ipv4Address source, const Ipv4Address next,
                     const uint32_t interface);

        void
        EnablePimInterface (uint32_t interface);
        void
        DisablePimInterface (uint32_t interface);
        bool
        GetPimInterface (uint32_t interface);

        Ipv4Address
        GetLocalAddress (uint32_t interface);
        bool
        isValidGateway (Ipv4Address gw);

        // From Ipv4RoutingProtocol
        virtual Ptr<Ipv4Route>
        RouteOutput (Ptr<Packet> p, const Ipv4Header &header, Ptr<NetDevice> oif, Socket::SocketErrno &sockerr);
        // From Ipv4RoutingProtocol
        virtual bool
        RouteInput (Ptr<const Packet> p, const Ipv4Header &header, Ptr<const NetDevice> idev,
                    UnicastForwardCallback ucb, MulticastForwardCallback mcb, LocalDeliverCallback lcb,
                    ErrorCallback ecb);
        // From Ipv4RoutingProtocol
        virtual void
        NotifyInterfaceUp (uint32_t interface);
        // From Ipv4RoutingProtocol
        virtual void
        NotifyInterfaceDown (uint32_t interface);
        // From Ipv4RoutingProtocol
        virtual void
        NotifyAddAddress (uint32_t interface, Ipv4InterfaceAddress address);
        // From Ipv4RoutingProtocol
        virtual void
        NotifyRemoveAddress (uint32_t interface, Ipv4InterfaceAddress address);
        // From Ipv4RoutingProtocol
        virtual void
        SetIpv4 (Ptr<Ipv4> ipv4);
        // From Ipv4RoutingProtocol
        virtual void
        PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const;
        Ptr<Ipv4Route>
        GetRoute (Ipv4Address source);

        void
        DoDispose ();

        void
        SetHelloHoldTime (uint16_t holdt);
        uint16_t
        GetHelloHoldTime ();

        void
        SetGenerationID (uint32_t gid);
        uint32_t
        GetGenerationID ();

        void
        SetStopTx ();

        void
        UnsetStopTx ();

        bool
        GetStopTx ();

        void
        AddMulticastRoute (Ipv4Address source, Ipv4Address group, uint32_t inputInterface,
                           std::vector<uint32_t> outputInterfaces);

        void
        AddMulticastGroup (Ipv4Address group);
        bool
        GetMulticastGroup (Ipv4Address group);
        void
        DelMulticastGroup (Ipv4Address group);

        /// The preference value assigned to the unicast routing protocol that provided the route to the source
        uint16_t
        GetMetricPreference (uint32_t interface);

        void
        SetMetricPreference (uint32_t interface, uint16_t metric)
        {
        }

        void
        SetRouteMetric (uint32_t interface, uint16_t metric)
        {
        }

        Ipv4Address
        GetNextHop (Ipv4Address destination);

        ///\name Fields for each interface
        /// Check that address is one of my interfaces
        bool
        IsMyOwnAddress (const Ipv4Address & a) const;

        bool
        IsValidSG (uint32_t interface, const Ipv4Address & source, const Ipv4Address & group);

//	uint32_t GetReceivingInterface (Ipv4Address addr);

        /// Threshold (I) returns the minimum TTL that a packet must have before it can be transmitted on interface I.
        uint8_t
        getThreshold (uint32_t interface);

        void
        Tokenize (const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = ",");
        void
        ParseSourceGroupInterface (std::string SGI, Ipv4Address &source, Ipv4Address &group, uint32_t &interface);
        Ipv4Header
        BuildHeader (Ipv4Address source, Ipv4Address destination, uint8_t protocol, uint16_t payloadSize, uint8_t ttl,
                     bool mayFragment);

        ///< Randomized delay to prevent response implosion when sending a join message to override someone else's prune
        /// t_override is a random value between 0 and the interface's Override_Interval (OI (I)).
        /// If all routers on a LAN are using the LAN Prune Delay option, the Override_Interval (OI (I)) MUST be set to the
        /// largest value on the LAN. Otherwise, the Override_Interval (OI (I)) MUST be set to 2.5 seconds.

        double
        t_override (uint32_t interface);

        /// Timer Name: Upstream Override Timer (OT (S,G)).
        double
        t_short (uint32_t interface);

        double
        OverrideInterval (uint32_t interface);

        PIMHeader::EncodedUnicast
        ForgeEncodedUnicast (Ipv4Address unicast);
        PIMHeader::EncodedGroup
        ForgeEncodedGroup (Ipv4Address group);
        PIMHeader::EncodedSource
        ForgeEncodedSource (Ipv4Address source);

        void
        ForgeHeaderMessage (enum PIMType type, PIMHeader &msg);
        void
        ForgeHelloMessage (uint32_t interface, PIMHeader &msg);
        void
        ForgeHelloMessageHoldTime (uint32_t interface, PIMHeader &msg);
        void
        ForgeHelloMessageLANPD (uint32_t interface, PIMHeader &msg);
        void
        ForgeHelloMessageGenID (uint32_t interface, PIMHeader &msg);
        void
        ForgeHelloMessageStateRefresh (uint32_t interface, PIMHeader &msg);

        void
        ForgeJoinPruneMessage (PIMHeader &msg, Ipv4Address const upstreamNeighbor);
        void
        ForgeAssertMessage (uint32_t interface, Ipv4Address destination, PIMHeader &msg, SourceGroupPair &sgp);
        void
        ForgeAssertCancelMessage (uint32_t interface, PIMHeader &msg, SourceGroupPair &sgp);
        void
        ForgeGraftMessage (uint32_t interface, PIMHeader &msg, SourceGroupPair &sgp, Ipv4Address upstreamNeighbor);

        void
        AddMulticastGroupEntry (PIMHeader &msg, PIMHeader::MulticastGroupEntry &entry);
        void
        CreateMulticastGroupEntry (PIMHeader::MulticastGroupEntry &m_entry, PIMHeader::EncodedGroup group);
        void
        AddMulticastGroupSourceJoin (PIMHeader::MulticastGroupEntry &m_entry, PIMHeader::EncodedSource source);
        void
        AddMulticastGroupSourcePrune (PIMHeader::MulticastGroupEntry &m_entry, PIMHeader::EncodedSource source);

        void
        SendHello (uint32_t interface);
        void
        SendHelloReply (uint32_t interface, Ipv4Address destination);
        void
        RecvHello (pimdm::PIMHeader::HelloMessage &hello, Ipv4Address sender, Ipv4Address receiver, uint32_t interface);

        void
        ForgeStateRefresh (uint32_t interface, Ipv4Address destination, SourceGroupPair &sgp, PIMHeader &msg);
        void
        SendStateRefreshMessage (uint32_t interface, Ipv4Address target, SourceGroupPair &sgpair);
        void
        RecvStateRefresh (PIMHeader::StateRefreshMessage &refresh, Ipv4Address sender, Ipv4Address receiver,
                          uint32_t interface);
        void
        ForwardingStateRefresh (PIMHeader::StateRefreshMessage &refresh, Ipv4Address sender, Ipv4Address receiver);

        void
        RecvJP (PIMHeader::JoinPruneMessage &jp, Ipv4Address sender, Ipv4Address receiver, uint32_t interface);

        void
        RecvJoin (PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface,
                  const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group);
        void
        RecvJoinUpstream (PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver,
                          uint32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group);
        void
        RecvJoinDownstream (PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver,
                            uint32_t &interface, const PIMHeader::EncodedSource &source,
                            PIMHeader::EncodedGroup &group);

        void
        RecvPrune (PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver, uint32_t &interface,
                   const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group);
        void
        RecvPruneUpstream (PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver,
                           uint32_t &interface, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group);
        void
        RecvPruneDownstream (PIMHeader::JoinPruneMessage &jp, Ipv4Address &sender, Ipv4Address &receiver,
                             uint32_t &interface, const PIMHeader::EncodedSource &source,
                             PIMHeader::EncodedGroup &group);

        void
        SendAssertCancelBroadcast (uint32_t interface, const Ipv4Address destination, SourceGroupPair &sgp);
        void
        SendAssertBroadcast (uint32_t interface, const Ipv4Address destination, SourceGroupPair &sgp);
        void
        SendAssertUnicast (SourceGroupPair &sgp, uint32_t interface, const Ipv4Address destination);
        void
        RecvAssert (PIMHeader::AssertMessage &assert, Ipv4Address sender, Ipv4Address receiver, uint32_t interface);

        void
        SendGraftBroadcast (uint32_t interface, Ipv4Address destination, SourceGroupPair pair);
        void
        SendGraftUnicast (Ipv4Address destination, SourceGroupPair pair);

        void
        RecvGraft (PIMHeader::GraftMessage &graft, Ipv4Address sender, Ipv4Address receiver, uint32_t interface);
        void
        RecvGraftDownstream (PIMHeader::GraftMessage &graft, Ipv4Address sender, Ipv4Address receiver,
                             const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group,
                             uint32_t interface);

        void
        ForgeGraftAckMessage (PIMHeader &msg, Ipv4Address upstreamNeighbor);
        void
        SendGraftAckBroadcast (uint32_t interface, const Ipv4Address receiver, SourceGroupPair &pair);
        void
        SendGraftAckUnicast (SourceGroupPair &pair, const Ipv4Address receiver);
        void
        RecvGraftAck (PIMHeader::GraftAckMessage &graftAck, Ipv4Address sender, Ipv4Address receiver,
                      uint32_t interface);

        void
        SendPruneBroadcast (uint32_t interface, SourceGroupPair &sgpair, Ipv4Address target);
        void
        SendPruneUnicast (Ipv4Address destination, SourceGroupPair &sgpair);

        void
        SendJoinBroadcast (uint32_t interface, Ipv4Address destination, SourceGroupPair &sgpair);
        void
        SendJoinUnicast (Ipv4Address destination, SourceGroupPair &sgpair);

        void
        RecvMessage (Ptr<Socket> packet);
        void
        RecvPIMDM (Ptr<Packet> receivedPacket, Ipv4Address senderIfaceAddr, uint16_t senderIfacePort,
                   uint32_t interface);
        void
        RecvPIMData (Ptr<Packet> receivedPacket, Ipv4Address senderIfaceAddr, uint16_t senderIfacePort,
                     uint32_t interface);

        void
        UpdateAssertTimer (SourceGroupPair &sgp, uint32_t interface, const Ipv4Address destination);
        void
        UpdateAssertTimer (SourceGroupPair &sgp, uint32_t interface, Time delay, const Ipv4Address destination);
        void
        UpdatePruneTimer (SourceGroupPair &sgp, uint32_t interface, const Ipv4Address destination);
        void
        UpdatePruneTimer (SourceGroupPair &sgp, uint32_t interface, Time delay, const Ipv4Address destination);
        void
        UpdatePruneDownstreamTimer (SourceGroupPair &sgp, uint32_t interface, const Ipv4Address destination);
        void
        UpdatePrunePendingTimer (SourceGroupPair &sgp, uint32_t interface, Time delay, const Ipv4Address destination);
        void
        UpdateGraftTimer (SourceGroupPair &sgp, uint32_t interface, Time delay, const Ipv4Address destination);
        void
        UpdateGraftTimer (SourceGroupPair &sgp, uint32_t interface, const Ipv4Address destination);
        void
        UpdateOverrideTimer (SourceGroupPair &sgp, uint32_t interface, Time delay, const Ipv4Address destination);
        void
        UpdateOverrideTimer (SourceGroupPair &sgp, uint32_t interface, const Ipv4Address destination);
        void
        UpdatePruneLimitTimer (SourceGroupPair &sgp, uint32_t interface, Time delay, const Ipv4Address destination);
        void
        UpdatePruneLimitTimer (SourceGroupPair &sgp, uint32_t interface, const Ipv4Address destination);
        void
        UpdateSourceActiveTimer (SourceGroupPair &sgp, uint32_t interface, Time delay, const Ipv4Address destination);
        void
        UpdateSourceActiveTimer (SourceGroupPair &sgp, uint32_t interface, const Ipv4Address destination);
        void
        UpdateStateRefreshTimer (SourceGroupPair &sgp, uint32_t interface, Time delay, const Ipv4Address destination);
        void
        UpdateStateRefreshTimer (SourceGroupPair &sgp, uint32_t interface, const Ipv4Address destination);
        void
        SendPacketPIMUnicast (Ptr<Packet> packet, const PIMHeader &message, Ipv4Address destination);
        void
        SendPacketHBroadcastInterface (Ptr<Packet> packet, Ipv4Header &ipv4Header, uint32_t interface);
        void
        SendPacketPIMRoutersInterface (Ptr<Packet> packet, const PIMHeader &message, uint32_t interface);
        void
        SendPacketUnicast (Ptr<Packet> packet, Ipv4Address destination);
        //end
        void
        NeighborRestart (uint32_t interface, Ipv4Address neighbor);

        void
        UpdateAssertWinner (SourceGroupState *sgState, uint32_t interface);
        void
        UpdateAssertWinner (SourceGroupState *sgState, uint32_t metricP, uint32_t routeP, Ipv4Address winner);
        void
        UpdateAssertWinner (SourceGroupState *sgState, AssertMetric update);

        void
        NeighborTimeout (uint32_t interface);
        /**
         * Downstream Interface.
         * All interfaces that are not the upstream interface, including the router itself.
         */
        bool
        IsDownstream (uint32_t interface, Ipv4Address destination, SourceGroupPair sgpair);
        bool
        IsDownstream (uint32_t interface, Ipv4Address neighbor, Ipv4Address source, Ipv4Address group);
        /**
         * Upstream Interface.
         * Interface toward the source of the datagram. Also known as the RPF Interface.
         */
        bool
        IsUpstream (uint32_t interface, Ipv4Address neighbor, SourceGroupPair sgpair);
        bool
        IsUpstream (uint32_t interface, Ipv4Address neighbor, Ipv4Address source, Ipv4Address group);

        void
        SendPacket (Ptr<Packet> packet, const PIMMessageList &containedMessages);

        void
        RenewTimerExpire (SourceGroupPair sgp);
        void
        SendRenew (SourceGroupPair sgp, uint32_t interface);

        void
        HelloTimerExpire (uint32_t interface);
        void
        OTTimerExpire (SourceGroupPair &sgp, uint32_t interface, Ipv4Address destination);
        void
        GRTTimerExpire (SourceGroupPair &sgp, uint32_t interface, Ipv4Address destination);
        void
        PLTTimerExpire (SourceGroupPair &sgp, uint32_t interface, Ipv4Address destination);
        void
        PLTTimerExpireDownstream (SourceGroupPair &sgp, uint32_t interface, Ipv4Address neighbor); //AX
        void
        ATTimerExpire (SourceGroupPair &sgp, uint32_t interface, Ipv4Address destination);
        void
        PPTTimerExpire (SourceGroupPair &sgp, uint32_t interface, Ipv4Address destination);
        void
        PTTimerExpire (SourceGroupPair &sgp, uint32_t interface, Ipv4Address destination);
        void
        NLTTimerExpire (uint32_t interface, Ipv4Address neighborIfaceAddr, Ipv4Address receivingIfaceAddr);
        void
        SRTTimerExpire (SourceGroupPair &sgp, uint32_t interface);
        void
        SATTimerExpire (SourceGroupPair &sgp, uint32_t interface, Ipv4Address destination);

        void
        UpstreamStateMachine (SourceGroupPair &sgp);

        void
        InsertSourceGroupList (uint32_t interface, Ipv4Address neighbor);
        SourceGroupList*
        FindSourceGroupList (uint32_t interface, Ipv4Address neighbor);
        void
        EraseSourceGroupList (uint32_t interface, Ipv4Address neighbor);
        void
        InsertSourceGroupState (uint32_t interface, Ipv4Address neighbor, SourceGroupPair sgp);
        SourceGroupState*
        FindSourceGroupState (uint32_t interface, Ipv4Address neighbor, const SourceGroupPair &sgp);
        SourceGroupState*
        FindSourceGroupState (uint32_t interface, Ipv4Address neighbor, const SourceGroupPair &sgp, bool add);
        SourceGroupState*
        FindSourceGroupState (uint32_t interface, Ipv4Address neighbor, const Ipv4Address source,
                              const Ipv4Address group);
        void
        EraseSourceGroupState (uint32_t interface, Ipv4Address neighbor, const SourceGroupPair &sgp);
        void
        EraseSourceGroupState (uint32_t interface, Ipv4Address neighbor, const Ipv4Address source,
                               const Ipv4Address group);
//	void ChangeSourceGroupState (uint32_t oldinterface, Ipv4Address oldneighbor, uint32_t newinterface, Ipv4Address newneighbor, const SourceGroupPair &sgp);

        void
        InsertNeighborhoodStatus (const uint32_t interface);
        NeighborhoodStatus*
        FindNeighborhoodStatus (uint32_t interface);
        void
        EraseNeighborhoodStatus (const uint32_t interface);

        void
        InsertNeighborState (uint32_t interface, const Ipv4Address neighbor, const Ipv4Address local);
        NeighborState*
        FindNeighborState (uint32_t interface, const NeighborState ns);
        NeighborState*
        FindNeighborState (uint32_t interface, const NeighborState ns, bool append);
        NeighborState*
        FindNeighborState (uint32_t interface, const Ipv4Address neighbor, const Ipv4Address local);

        void
        EraseNeighborState (uint32_t interface, const NeighborState &ns);

        void
        SetLANDelayEnabled (uint32_t interface, bool state);
        void
        SetPropagationDelay (uint32_t interface, Time delay);

        void
        SetOverrideInterval (uint32_t interface, Time interval);

        void
        GetPrinterList (std::string string, std::set<WiredEquivalentInterface> resB);

        ///
        /// \brief The most important macros are those defining the outgoing
        ///  interface list (or "olist") for the relevant state.
        ///  immediate_olist (S,G) = pim_nbrs (-) prunes (S,G) (+) ( pim_include (*,G) (-) pim_exclude (S,G) ) (+)
        ///              pim_include (S,G) (-) lost_assert (S,G) (-) boundary (G)
        /// \param source Source IPv4 address
        /// \param group Multicast group IPv4 address
        ///
        std::set<WiredEquivalentInterface>
        immediate_olist (Ipv4Address source, Ipv4Address group);
        void
        SourceDirectlyConnected (SourceGroupPair &sgp);
        void
        SourceNoDirectlyConnected (SourceGroupPair &sgp, uint32_t interface, Ipv4Address gateway);
        /// Basically RPF' is the RPF neighbor toward a source
        /// unless a PIM-DM Assert has overridden the normal choice of neighbor.

        void
        RPF_primeChanges (SourceGroupPair &sgp, uint32_t interfaceO, Ipv4Address gatewayO, uint32_t interfaceN,
                          Ipv4Address gatewayN);

        void
        RPF_Changes (SourceGroupPair &sgp, uint32_t oldInterface, Ipv4Address oldGateway, uint32_t newInterface,
                     Ipv4Address newGateway);

        bool
        RPFCheck (SourceGroupPair sgp);	//, uint32_t interface);//, Ptr<Ipv4Route> rpf_route);
        void
        RPFCheckAll ();

        void
        olistCheck (SourceGroupPair &sgp, std::set<WiredEquivalentInterface> &list);
        void
        olistEmpty (SourceGroupPair &sgp);
        void
        olistFull (SourceGroupPair &sgp);

        /// \brief The outgoing interfaces except the RPF_interface.
        ///
        /// \param source Source IPv4 address
        /// \param group Multicast group IPv4 address
        std::set<WiredEquivalentInterface>
        olist (Ipv4Address source, Ipv4Address group);

        /// \brief RPF interface towards the source S as indicated by the MRIB.
        /// \param source Source IPv4 address
        WiredEquivalentInterface
        RPF_interface (Ipv4Address source);
        WiredEquivalentInterface
        RPF_interface (Ipv4Address source, Ipv4Address group);

        /// \brief Find the route for on-demand routing protocols.
        /// \param destination Node to lookup.
        void
        AskRoute (Ipv4Address destination);
        void
        AskRoutez (Ipv4Address destination);

        /// \brief There are receivers for the given SourceGroup pair.
        /// \param sgp source-group pair.
        /// \return True if there are receivers interested in, false otherwise.
        bool
        GetLocalReceiver (SourceGroupPair sgp);

        /// \brief There are receivers for the given SourceGroup pair on that interface.
        /// \param sgp source-group pair.
        /// \param interface node interface
        /// \return True if there are receivers on the particular interface that are interested in, false otherwise.
        bool
        GetLocalReceiverInterface (SourceGroupPair sgp, uint32_t interface);

        /*
         * The macro local_receiver_include (S,G,I) is true if the IGMP module or
         * other local membership mechanism has determined that there are local
         * members on interface I that seek to receive traffic sent specifically by S to G.
         */
        bool
        local_receiver_include (Ipv4Address source, Ipv4Address group, uint32_t interface);

        //
        ///The interfaces to which traffic might be forwarded because
        //  of hosts that are local members on those interfaces.
        //
        //  pim_include (*,G) = {all interfaces I such that: local_receiver_include (*,G,I)}
        //  pim_include (S,G) = {all interfaces I such that: local_receiver_include (S,G,I)}
        std::set<WiredEquivalentInterface>
        pim_include (Ipv4Address source, Ipv4Address group);

        bool
        seek_traffic_from (Ipv4Address source, Ipv4Address group, uint32_t interface);

        // Local members for a (source,group) pair.
        // True if local_receiver_include (*,G,I) is true
        // but none of the local members seek to receive traffic from S.
        bool
        local_receiver_exclude (Ipv4Address source, Ipv4Address group, uint32_t interface);

        /// The interfaces to which traffic might not be forwarded because of hosts that are not local members on those interfaces.
        ///  pim_exclude (S,G) = {all interfaces I such that: local_receiver_exclude (S,G,I)}
        std::set<WiredEquivalentInterface>
        pim_exclude (Ipv4Address source, Ipv4Address group);

        bool
        IsLoopInterface (uint32_t interface);

        /*
         * All interfaces on which the router has at least one active PIM neighbor.
         */
        std::set<WiredEquivalentInterface>
        pim_nbrs (void);

        /*
         * The set of all interfaces on which the router has received Prune (S,G) messages:
         *   prunes (S,G) = {all interfaces I such that DownstreamPState (S,G,I) is in Pruned state}
         */
        std::set<WiredEquivalentInterface>
        prunes (Ipv4Address source, Ipv4Address group);

        /* The set lost_assert (S,G) is the set of all interfaces on which the
         *  router has lost an (S,G) Assert.
         *  lost_assert (S,G) = {all interfaces I such that
         *            lost_assert (S,G,I) == TRUE}
         *
         */
        std::set<WiredEquivalentInterface>
        lost_assert (Ipv4Address source, Ipv4Address group);

        /*
         * True if the node has lost an (S,G) Assert on that interface.
         */
        bool
        lost_assert (Ipv4Address source, Ipv4Address group, uint32_t interface, Ipv4Address neighbor);

        //AssertWinner (S,G,I) defaults to NULL -> ANY
        Ipv4Address
        AssertWinner (Ipv4Address source, Ipv4Address group, uint32_t interface, Ipv4Address neighbor);

        struct AssertMetric
        AssertWinnerMetric (Ipv4Address source, Ipv4Address group, uint32_t interface, Ipv4Address neighbor);
        bool
        boundary (uint32_t interface, Ipv4Address group);

        /*
         * boundary (G) = {all interfaces I with an administratively scoped boundary for group G}
         */
        std::set<WiredEquivalentInterface>
        boundary (Ipv4Address G);

        //The macro I_Am_Assert_loser (S, G, I) is true if the Assert state
        //  machine (in Section 4.6) for (S,G) on interface I is in the "I am
        //  Assert Loser" state.
        Ipv4Address
        RPF_prime (Ipv4Address source, Ipv4Address group);
        bool
        I_Am_Assert_loser (Ipv4Address source, Ipv4Address group, uint32_t interface, Ipv4Address nexthop);

        void
        CouldAssertCheck (Ipv4Address source, Ipv4Address group, uint32_t interface, Ipv4Address destination,
                          bool couldAssert);

        bool
        CouldAssert (Ipv4Address source, Ipv4Address group, uint32_t interface, Ipv4Address neighbor);

        struct AssertMetric
        spt_assert_metric (Ipv4Address source, uint32_t interface);

        struct AssertMetric
        infinite_assert_metric ();

        struct AssertMetric
        my_assert_metric (Ipv4Address source, Ipv4Address group, uint32_t interface, Ipv4Address neighbor);

        //StateRefreshRateLimit (S,G) is TRUE if the time elapsed since the last received StateRefresh (S,G)
        //	is less than the configured RefreshLimitInterval.
        bool
        StateRefreshRateLimit (Ipv4Address source, Ipv4Address group);

        bool
        StateRefreshCapable (uint32_t interface);

        void
        SetPruneState (uint32_t interface, Ipv4Address neighbor, SourceGroupPair sgp, PruneState state);
        Time
        TransmissionDelay (double l, double u, enum Time::Unit unit);
        Time
        TransmissionDelay (double l, double u);
        Time
        TransmissionDelay ();
    };

    struct IdTag : public Tag
    {
        uint32_t m_id;
        IdTag (uint32_t id = 0) :
            Tag(), m_id(id)
        {
        }

        static TypeId
        GetTypeId ()
        {
          static TypeId tid = TypeId("ns3::IdTag").SetParent<Tag>();
          return tid;
        }

        TypeId
        GetInstanceTypeId (void) const
        {
          return GetTypeId();
        }

        uint32_t
        GetSerializedSize (void) const
        {
          return sizeof(m_id);
        }

        void
        Serialize (TagBuffer i) const
        {
          i.WriteU32(m_id);
        }

        void
        Deserialize (TagBuffer i)
        {
          m_id = i.ReadU32();
        }

        void
        Print (std::ostream &os) const
        {
          os << " IdTag: id " << m_id;
        }

    };

    struct RelayTag : public Tag
    {
        Ipv4Address m_sender;
        Ipv4Address m_receiver;
        RelayTag (Ipv4Address sender = Ipv4Address::GetAny(), Ipv4Address receiver = Ipv4Address::GetAny()) :
            Tag(), m_sender(sender), m_receiver(receiver)
        {
        }

        static TypeId
        GetTypeId ()
        {
          static TypeId tid = TypeId("ns3::RelayTag").SetParent<Tag>();
          return tid;
        }

        TypeId
        GetInstanceTypeId (void) const
        {
          return GetTypeId();
        }

        uint32_t
        GetSerializedSize (void) const
        {
          return sizeof(m_sender) + sizeof(m_receiver);
        }

        void
        Serialize (TagBuffer i) const
        {
          i.WriteU32(m_sender.Get());
          i.WriteU32(m_receiver.Get());
        }

        void
        Deserialize (TagBuffer i)
        {
          m_sender = Ipv4Address(i.ReadU32());
          m_receiver = Ipv4Address(i.ReadU32());
        }

        void
        Print (std::ostream &os) const
        {
          os << " RelayTag: Sender " << m_sender << ", Receiver " << m_receiver;
        }
    };
  } // namespace pimdm
} // namespace ns3
#endif // __PIM_DM_ROUTING_H__
