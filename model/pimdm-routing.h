/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 University of Trento, Italy
 * 					 University of California, Los Angeles, U.S.A.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *
 * Authors: Alessandro Russo <russo@disi.unitn.it>
 *     University of Trento, Italy
 *     University of California, Los Angeles U.S.A.
 */

/// \brief	This header file declares and defines internal state of an PIM-DM node.

#ifndef __PIM_DM_ROUTING_H__
#define __PIM_DM_ROUTING_H__

/// Time default value for RPF check.
#define RPF_CHECK 5
/// Timer Name: Hello Timer (HT). Periodic interval for hello messages.
#define Hello_Period 30
/// Timer Name: Hello Timer (HT). Random interval for initial Hello message on bootup or triggered Hello message to a rebooting neighbor.
#define Triggered_Hello_Delay 5
/// The Hold Time in the Hello Message should be set to a value that can
///  reasonably be expected to keep the Hello active until a new Hello
///  message is received. On most links, this will be 3.5 times the value
///  of Hello_Period.
#define Hold_Time_Default (3.5*Hello_Period) //seconds
/// Timer Name: Assert Timer (AT (S,G,I)). Period after last assert before assert state is timed out.
#define Assert_Time 180
/// Timer Name: Graft Retry Timer (GRT (S,G)). In the absence of receipt of a GraftAck message, the time before retransmission of a Graft message.
#define Graft_Retry_Period 3
/// Used to prevent Prune storms on a LAN.
#define t_limit 210
/// Timer Name: Upstream Override Timer (OT (S,G)).
#define t_short t_override
#define t_shorter 2
/// Timer Name: Source Active Timer (SAT (S,G)).
///  Period of time after receiving a multicast message a directly
///  attached router will continue to send State Refresh messages.
#define SourceLifetime 210
/// Timer Name: State Refresh Timer (SRT (S,G)).
///  Interval between successive state refresh messages.
#define RefreshInterval 60
#define StateRefreshInterval RefreshInterval
/// If all routers on a LAN are using the LAN Prune Delay option, the Override_Interval (OI (I)) MUST be set to the
///  largest value on the LAN. Otherwise, the Override_Interval (OI (I)) MUST be set to 2.5 seconds.
#define Override_Interval 2.5
// The J/P_Override_Interval is the sum of the interface's
//	 Override_Interval (OI (I)) and Propagation_Delay (PD (I)). If all
//	 routers on a LAN are using the LAN Prune Delay option, both
//	 parameters MUST be set to the largest value on the LAN. Otherwise,
//	 the Override_Interval (OI (I)) MUST be set to 2.5 seconds, and the
//	 Propagation_Delay (PD (I)) MUST be set to 0.5 seconds.
#define Propagation_Delay 0.5
// The number of seconds a receiving PIM-DM router MUST keep a Prune
//   state alive, unless removed by a Join or Graft message. If the
//   Hold Time is '0xffff', the receiver MUST NOT remove the Prune state
//   unless a corresponding Join or Graft message is received. The Hold
//   Time is ignored in Join messages.
#define PruneHoldTime 0xffff
// The number of seconds a receiving PIM-DM router MUST keep a Prune
//   state alive, unless removed by a Join or Graft message. If the
//   Hold Time is '0xffff', the receiver MUST NOT remove the Prune state
//   unless a corresponding Join or Graft message is received. The Hold
//   Time is ignored in Join messages.
#define PruneHoldTime 0xffff
//If all routers on a LAN support the LAN Prune Delay option, then the
//  PIM routers on that LAN will use the values received to adjust their
//  J/P_Override_Interval on that interface and the interface is LAN
//  Delay Enabled. Briefly, to avoid synchronization of Prune Override
//  (Join) messages when multiple downstream routers share a multi-access
//  link, sending of these messages is delayed by a small random amount
//  of time. The period of randomization is configurable and has a
//  default value of 3 seconds.
#define JoinDelay 3 //Prune override
#define TTL_SAMPLE .2
#define PIM_RESERVED 0
#define PIM_PORT_NUMBER 703 //IANA Unassigned

#include "ns3/test.h"
#include "pimdm-structure.h"
#include "pimdm-packet.h"

#include "ns3/tag.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"

#include "ns3/random-variable.h"
#include "ns3/object.h"
#include "ns3/packet.h"
#include "ns3/node.h"
#include "ns3/socket.h"
#include "ns3/event-garbage-collector.h"
#include "ns3/timer.h"
#include "ns3/traced-callback.h"
#include "ns3/ipv4.h"
#include "ns3/ipv4-routing-protocol.h"
#include "ns3/ipv4-static-routing.h"
#include "ns3/ipv4-list-routing.h"
#include "ns3/ipv4-l3-protocol.h"
#include "ns3/string.h"
#include "ns3/aodv-rtable.h"
#include "ns3/aodv-routing-protocol.h"
#include "ns3/mbn-aodv-routing-protocol.h"
#include "ns3/mbn-aodv-common.h"
#include "ns3/olsr-routing-protocol.h"
#include "ns3/dsdv-rtable.h"
#include "ns3/dsdv-routing-protocol.h"

#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <iterator>

namespace ns3 {
namespace pimdm {
struct MulticastEntry {
	Ipv4Address sourceAddr; ///< source destination
	Ipv4Address nextAddr; ///< source destination
	int32_t interface; ///< interface to source
	MulticastEntry () : // default values
		sourceAddr (), nextAddr (), interface (0) {
	}
	;
};


struct RoutingMulticastTable {
	Ipv4Address groupAddr; ///< multicast group address
	std::map <Ipv4Address,MulticastEntry> mgroup; ///< source destination
	RoutingMulticastTable () : // default values
		groupAddr () {
	}
	;
};

/// This class encapsulates all data structures needed for maintaining internal state of an PIM_DM node.
class MulticastRoutingProtocol: public Ipv4RoutingProtocol {
	// friend class;
private:
	int32_t m_mainInterface; ///< Node main interface.
	Ipv4Address m_mainAddress; ///< Main address on the main interface.

	// static routing table
	Ptr<Ipv4StaticRouting> m_RoutingTable;

	typedef std::list<Ipv4MulticastRoutingTableEntry *> MulticastRoutes;
  MulticastRoutes m_multicastRoutes;

	///\name Protocol fields;
	//\{
	std::map<int32_t, NeighborhoodStatus> m_IfaceNeighbors; ///< Information on interface and neighbors (RFC 3973, section 4.1.1).
	///TIB - Tree Information Base
	std::map<WiredEquivalentInterface, SourceGroupList> m_IfaceSourceGroup; ///< List of (S,G) pair state (RFC 3973, section 4.1.2).

	std::map<SourceGroupPair, std::set<int32_t> > m_LocalReceiver;

	///pim ENABLED INTERFACES
	std::map<int32_t, bool> m_IfacePimEnabled; //TODO, right now all interfaces are pim enabled.
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
	std::map<Ptr<Socket> , Ipv4InterfaceAddress> m_socketAddresses;
	/// Pointer to socket.
	Ptr<Ipv4RoutingProtocol>* m_routingProtocol;
	/// Loopback device used to defer RREQ until packet will be fully formed
	Ptr<NetDevice> m_lo;
	//}

	/// A list of pending messages which are buffered awaiting for being sent.
	pimdm::PIMHeader m_queuedMessages;
	Timer m_queuedMessagesTimer; // timer for throttling outgoing messages

	Time m_rpfCheck;
	Timer m_rpfChecker;

	Time m_LanDelay;
	uint64_t m_latestPacketID;

	TracedCallback <const PIMHeader &> m_rxPacketTrace;
	TracedCallback <const PIMHeader &> m_txPacketTrace;

	TracedCallback<uint32_t> m_routingTableChanged;

protected:
	virtual void DoStart (void);

public:
	static TypeId GetTypeId (void);

	MulticastRoutingProtocol ();
	virtual ~MulticastRoutingProtocol ();

	int32_t GetMainInterface () {
		return m_mainInterface;
	}

	void SetInterfaceExclusions (std::set<uint32_t> exceptions);
	std::set<uint32_t> GetInterfaceExclusions () const {
		return m_interfaceExclusions;
	}
	/**
	 * Return the list of routing table entries discovered by OLSR
	 **/
	std::vector<RoutingMulticastTable> GetRoutingTableEntries () const;

	void register_member (std::string SGI);

	void UpdateMRIB (){}


private:
	void Clear ();
	uint32_t GetSize () const {
		return m_mrib.size ();
	}

	void RemoveEntry (const Ipv4Address &group);
	void RemoveEntry (const Ipv4Address &group, const Ipv4Address &source);
	void AddEntry (const Ipv4Address group, const Ipv4Address source, const Ipv4Address next, const int32_t interface);
	bool Lookup (const Ipv4Address group, RoutingMulticastTable &outEntry) const;
	bool Lookup (const Ipv4Address group, const Ipv4Address source, RoutingMulticastTable &outEntry, MulticastEntry &me) const;
	bool UpdateEntry (const Ipv4Address group, const Ipv4Address source, const Ipv4Address next, const int32_t interface) ;

	void EnablePimInterface(int32_t interface){
		if(m_IfacePimEnabled.find(interface) == m_IfacePimEnabled.end())
			m_IfacePimEnabled.insert(std::pair<int32_t,bool>(interface,true));
		else m_IfacePimEnabled.find(interface)->second = true;
	}

	void DisablePimInterface(int32_t interface){
		if(m_IfacePimEnabled.find(interface) == m_IfacePimEnabled.end())
			m_IfacePimEnabled.insert(std::pair<int32_t,bool>(interface,false));
		else m_IfacePimEnabled.find(interface)->second = false;
	}

	bool GetPimInterface(int32_t interface){
		if(m_IfacePimEnabled.find(interface) == m_IfacePimEnabled.end())
			return false;
		else
			return m_IfacePimEnabled.find(interface)->second;
	}

	Ipv4Address GetLocalAddress (int32_t interface);

	// From Ipv4RoutingProtocol
	virtual Ptr<Ipv4Route> RouteOutput (Ptr<Packet> p, const Ipv4Header &header,Ptr<NetDevice> oif, Socket::SocketErrno &sockerr);
	// From Ipv4RoutingProtocol
	virtual bool RouteInput (Ptr<const Packet> p, const Ipv4Header &header,Ptr<const NetDevice> idev, UnicastForwardCallback ucb,
			MulticastForwardCallback mcb, LocalDeliverCallback lcb,ErrorCallback ecb);
	// From Ipv4RoutingProtocol
	virtual void NotifyInterfaceUp (uint32_t interface);
	// From Ipv4RoutingProtocol
	virtual void NotifyInterfaceDown (uint32_t interface);
	// From Ipv4RoutingProtocol
	virtual void NotifyAddAddress (uint32_t interface,Ipv4InterfaceAddress address);
	// From Ipv4RoutingProtocol
	virtual void NotifyRemoveAddress (uint32_t interface,Ipv4InterfaceAddress address);
	// From Ipv4RoutingProtocol
	virtual void SetIpv4 (Ptr<Ipv4> ipv4);
	// From Ipv4RoutingProtocol
	virtual void PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const;
	Ptr<Ipv4Route> GetRoute (Ipv4Address source);

	void DoDispose ();

	void SetHelloHoldTime (uint16_t holdt){
		m_helloHoldTime = holdt;
	}

	uint16_t GetHelloHoldTime (){
		return m_helloHoldTime;
	}

	void SetGenerationID (uint32_t gid) {
		m_generationID = gid;
	}
	uint32_t GetGenerationID () {
		return m_generationID;
	}

	void SetStopTx () {
		m_stopTx = true;
	}

	void UnsetStopTx () {
		m_stopTx = false;
	}

	bool GetStopTx (){
		return m_stopTx;
	}

	void AddMulticastRoute (Ipv4Address source, Ipv4Address group, int32_t inputInterface, std::vector<int32_t> outputInterfaces);

	void AddMulticastGroup (Ipv4Address group);
	bool GetMulticastGroup (Ipv4Address group){
		return (group.IsMulticast () && m_mrib.find (group)!=m_mrib.end ());
	}

	void DelMulticastGroup (Ipv4Address group){
		if (group.IsMulticast () && GetMulticastGroup (group)){
			m_mrib.find(group)->second.mgroup.clear();
			m_mrib.erase (group);
		}
	}

	/// The preference value assigned to the unicast routing protocol that provided the route to the source
	uint16_t GetMetricPreference (int32_t interface);

	void SetMetricPreference (int32_t interface, uint16_t metric){}

	/// The cost metric of the unicast route to the source. The metric is in units applicable to the unicast routing protocol used.
	uint16_t GetRouteMetric (int32_t interface, Ipv4Address source);

	void SetRouteMetric (int32_t interface, uint16_t metric){}

	Ipv4Address GetNextHop (Ipv4Address destination);

	///\name Fields for each interface
	/// Check that address is one of my interfaces
	bool IsMyOwnAddress (const Ipv4Address & a) const;

	bool IsValidSG (int32_t interface, const Ipv4Address & source,const Ipv4Address & group);

	bool UsesNonPimDmOutgoingInterface (const Ipv4RoutingTableEntry &route);

	int32_t GetReceivingInterface (Ipv4Address addr){
		int32_t interface = -1;
		if (!addr.IsMulticast ()){
			Ptr<Ipv4Route> route = GetRoute (addr);
			if(route){
				Ptr<NetDevice> dev = route->GetOutputDevice ();
				interface = m_ipv4->GetInterfaceForDevice (dev);
			}
		}
		return interface;
	}

	/// Threshold (I) returns the minimum TTL that a packet must have before it can be transmitted on interface I.
	uint32_t getThreshold (int32_t interface){
		return 2; //TODO check what is it
	}

	void ParseSourceGroupInterface(std::string SGI, Ipv4Address &source, Ipv4Address &group, int32_t &interface){
		// Just to get the IP info
		size_t p = SGI.find(",");
		size_t l = SGI.find(",",p+1);
		size_t m = SGI.length() ;
		std::string groupS = SGI.substr(0,p);
		std::string sourceS = SGI.substr(p+1,l-p-1);
		std::string ifaceS = SGI.substr(l+1,m);
		group = Ipv4Address(groupS.c_str());
		source = Ipv4Address(sourceS.c_str());
		interface = atoi(ifaceS.c_str());
	}

	Ipv4Header BuildHeader (Ipv4Address source, Ipv4Address destination, uint8_t protocol, uint16_t payloadSize, uint8_t ttl, bool mayFragment)
	{
		Ipv4Header ipv4header;
		ipv4header.SetSource(source);
		ipv4header.SetDestination(destination);
		ipv4header.SetProtocol(protocol);
		ipv4header.SetPayloadSize(payloadSize);
		ipv4header.SetTtl(ttl);
		if(mayFragment){
			ipv4header.SetMayFragment();
			ipv4header.SetIdentification(m_identification);
			m_identification++;
		}
		else {
			ipv4header.SetDontFragment ();
			ipv4header.SetIdentification (m_identification);
			m_identification++;
		}
		if (Node::ChecksumEnabled ()){
			ipv4header.EnableChecksum ();
		}
		return ipv4header;
	}

	///< Randomized delay to prevent response implosion when sending a join message to override someone else's prune
	/// t_override is a random value between 0 and the interface's Override_Interval (OI (I)).
	/// If all routers on a LAN are using the LAN Prune Delay option, the Override_Interval (OI (I)) MUST be set to the
	/// largest value on the LAN. Otherwise, the Override_Interval (OI (I)) MUST be set to 2.5 seconds.

	uint32_t t_override (int32_t interface){
		return UniformVariable ().GetValue (0, OverrideInterval (interface));
	}

	uint32_t OverrideInterval (int32_t interface){
			NeighborhoodStatus *ns = FindNeighborhoodStatus (interface);
			bool LPDO = true;
			for (std::list<NeighborState>::iterator iter = ns->neighbors.begin (); iter!=ns->neighbors.end () && LPDO; iter++){
				LPDO = LPDO && (iter->neighborOverrideInterval.GetSeconds ()>0);
				ns->overrideInterval = Max (ns->overrideInterval ,iter->neighborOverrideInterval);
			}
			return (LPDO?ns->overrideInterval.GetSeconds ():Override_Interval);
	}

	PIMHeader::EncodedUnicast ForgeEncodedUnicast (Ipv4Address unicast){
			PIMHeader::EncodedUnicast egroup = {AF_IPv4, NATIVE_ENCODING, unicast};
			return egroup;
		}

	PIMHeader::EncodedGroup ForgeEncodedGroup (Ipv4Address group){
		PIMHeader::EncodedGroup egroup = {AF_IPv4, NATIVE_ENCODING, 0, 0, 0, IPV4_ADDRESS_SIZE, group};
		return egroup;
	}

	PIMHeader::EncodedSource ForgeEncodedSource (Ipv4Address source){
		PIMHeader::EncodedSource esource = {AF_IPv4, NATIVE_ENCODING, 0, 0, 0, 0, IPV4_ADDRESS_SIZE, source};
		return esource;
	}

	void ForgeHeaderMessage (enum PIMType type, PIMHeader &msg);
	void ForgeHelloMessage (int32_t interface, PIMHeader &msg);
	void ForgeHelloMessageHoldTime (int32_t interface, PIMHeader &msg);
	void ForgeHelloMessageLANPD (int32_t interface, PIMHeader &msg);
	void ForgeHelloMessageGenID (int32_t interface, PIMHeader &msg);
	void ForgeHelloMessageStateRefresh (int32_t interface, PIMHeader &msg);

	void ForgeJoinPruneMessage (PIMHeader &msg, Ipv4Address const upstreamNeighbor);
	void ForgeAssertMessage (int32_t interface, Ipv4Address destination, PIMHeader &msg, SourceGroupPair &sgp);
	void ForgeAssertCancelMessage (int32_t interface, PIMHeader &msg, SourceGroupPair &sgp);
	void ForgeGraftMessage (int32_t interface, PIMHeader &msg, SourceGroupPair &sgp, Ipv4Address upstreamNeighbor);

	void AddMulticastGroupEntry (PIMHeader &msg,PIMHeader::MulticastGroupEntry &entry);
	void CreateMulticastGroupEntry (PIMHeader::MulticastGroupEntry &m_entry,PIMHeader::EncodedGroup group);
	void AddMulticastGroupSourceJoin (PIMHeader::MulticastGroupEntry &m_entry,PIMHeader::EncodedSource source);
	void AddMulticastGroupSourcePrune (PIMHeader::MulticastGroupEntry &m_entry,PIMHeader::EncodedSource source);

	void SendHello (int32_t interface);
	void SendHelloReply (int32_t interface, Ipv4Address destination);
	void RecvHello (pimdm::PIMHeader::HelloMessage &hello, Ipv4Address sender, Ipv4Address receiver, int32_t interface);

 	void ForgeStateRefresh (int32_t interface, Ipv4Address destination, SourceGroupPair &sgp, PIMHeader &msg);
	void SendStateRefreshMessage (int32_t interface, Ipv4Address target,SourceGroupPair &sgpair);
	void RecvStateRefresh (PIMHeader::StateRefreshMessage &refresh,Ipv4Address sender, Ipv4Address receiver, int32_t interface);
	void ForwardingStateRefresh (PIMHeader::StateRefreshMessage &refresh,Ipv4Address sender, Ipv4Address receiver);

	void RecvJP (PIMHeader::JoinPruneMessage &jp, Ipv4Address sender,Ipv4Address receiver, int32_t interface);

	void RecvJoin (PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group);
	void RecvJoinUpstream (PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group);
	void RecvJoinDownstream (PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group);

	void RecvPrune (PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group);
	void RecvPruneUpstream (PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group);
	void RecvPruneDownstream (PIMHeader::JoinPruneMessage &jp,Ipv4Address &sender, Ipv4Address &receiver, int32_t &interface, const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group);

	void RecvAssert (PIMHeader::AssertMessage &assert, Ipv4Address sender,Ipv4Address receiver, int32_t interface);

	void SendGraftUnicast (Ipv4Address destination,SourceGroupPair pair);

	void RecvGraft (PIMHeader::GraftMessage &graft, Ipv4Address sender, Ipv4Address receiver, int32_t interface);
	void RecvGraftDownstream (PIMHeader::GraftMessage &graft, Ipv4Address sender, Ipv4Address receiver, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group, int32_t interface);

	void ForgeGraftAckMessage (PIMHeader &msg, Ipv4Address upstreamNeighbor);
	void SendGraftAckUnicast (SourceGroupPair &pair, const Ipv4Address receiver);
	void RecvGraftAck (PIMHeader::GraftAckMessage &graftAck, Ipv4Address sender,Ipv4Address receiver, int32_t interface);

	void SendPruneBroadcast (int32_t interface, SourceGroupPair &sgpair);
	void SendPruneUnicast (Ipv4Address destination, SourceGroupPair &sgpair);

	void SendJoinUnicast (Ipv4Address destination, SourceGroupPair &sgpair);

	void RecvData (Ptr<Socket> socket);
	void SendPacketPIMUnicast (Ptr<Packet> packet, const PIMHeader &message, Ipv4Address destination);
	void SendPacketHBroadcastInterface (Ptr<Packet> packet, Ipv4Header &ipv4Header, int32_t interface);
	void SendPacketPIMRouters (Ptr<Packet> packet, const PIMHeader &message);
	void SendPacketPIMRoutersInterface (Ptr<Packet> packet, const PIMHeader &message, int32_t interface);
	void SendPacketUnicast (Ptr<Packet> packet, Ipv4Address destination);
	//end
	void NeighborRestart (int32_t interface, Ipv4Address neighbor);

	void RecvPimDm (Ptr<Socket> socket);

	void UpdateAssertWinner (SourceGroupState *sgState, int32_t interface){
			sgState->AssertWinner.metricPreference = GetMetricPreference (interface);
			sgState->AssertWinner.routeMetric = GetRouteMetric (interface,sgState->SGPair.sourceMulticastAddr);
			sgState->AssertWinner.IPAddress = GetLocalAddress (interface);
		}

	void UpdateAssertWinner (SourceGroupState *sgState, uint32_t metricP, uint32_t routeP, Ipv4Address winner){
			sgState->AssertWinner.metricPreference = metricP;
			sgState->AssertWinner.routeMetric = routeP;
			sgState->AssertWinner.IPAddress = winner;
		}

	void NeighborTimeout (int32_t interface);
	/**
	 * Downstream Interface.
	 * All interfaces that are not the upstream interface, including the router itself.
	 */
	bool IsDownstream (int32_t interface, Ipv4Address destination, SourceGroupPair sgpair);
	bool IsDownstream (int32_t interface, Ipv4Address neighbor, Ipv4Address source);
	/**
	 * Upstream Interface.
	 * Interface toward the source of the datagram. Also known as the RPF Interface.
	 */
	bool IsUpstream (int32_t interface, Ipv4Address neighbor, SourceGroupPair sgpair);
	bool IsUpstream (int32_t interface, Ipv4Address neighbor, Ipv4Address source);

	void SendPacket (Ptr<Packet> packet, const PIMMessageList &containedMessages);

	void HelloTimerExpire (int32_t interface);
	void OTTimerExpire (SourceGroupPair &sgp, int32_t interface);
	void GRTTimerExpire (SourceGroupPair &sgp, int32_t interface, Ipv4Address destination);
	void PLTTimerExpire (SourceGroupPair &sgp, Ipv4Address destination);
	void ATTimerExpire (SourceGroupPair &sgp, int32_t interface, Ipv4Address destination);
	void PPTTimerExpire (SourceGroupPair &sgp, int32_t interface, Ipv4Address destination);
	void PTTimerExpire (SourceGroupPair &sgp, int32_t interface);
	void NLTTimerExpire (Ipv4Address neighborIfaceAddr, Ipv4Address receivingIfaceAddr, int32_t interface);
	void SRTTimerExpire (SourceGroupPair &sgp, int32_t interface);
	void SATTimerExpire (SourceGroupPair &sgp, int32_t interface, Ipv4Address destination);

	void UpstreamStateMachine(SourceGroupPair &sgp);

	SourceGroupList* FindSourceGroupList (int32_t interface, Ipv4Address neighbor) {
		std::map<WiredEquivalentInterface, SourceGroupList>::iterator iter =
				m_IfaceSourceGroup.find (WiredEquivalentInterface(interface,neighbor));
		return (iter == m_IfaceSourceGroup.end () ? NULL : &iter->second);
	}

	void InsertSourceGroupList (int32_t interface, Ipv4Address neighbor) {
		WiredEquivalentInterface i_n (interface,neighbor);
		std::map<WiredEquivalentInterface, SourceGroupList>::iterator iter =
				m_IfaceSourceGroup.find (i_n);
		if (iter != m_IfaceSourceGroup.end ())
			return;
		SourceGroupList sgl;
		std::pair<WiredEquivalentInterface , SourceGroupList> i_s (i_n, sgl);
		m_IfaceSourceGroup.insert (i_s);
	}

	void EraseSourceGroupList (int32_t interface, Ipv4Address neighbor) {
		m_IfaceSourceGroup.erase (WiredEquivalentInterface(interface,neighbor));
	}

	SourceGroupState* FindSourceGroupState (int32_t interface, Ipv4Address neighbor, const SourceGroupPair &sgp) {
			SourceGroupList *sgl = FindSourceGroupList (interface,neighbor);
			if (!sgl)
				return NULL;
			for (SourceGroupList::iterator iter = sgl->begin (); iter != sgl->end (); iter++) {
				if (iter->SGPair == sgp)
					return & (*iter);
			}
			return NULL;
		}

	SourceGroupState* FindSourceGroupState (int32_t interface, Ipv4Address neighbor, const SourceGroupState &sgs) {
		SourceGroupList *sgl = FindSourceGroupList (interface,neighbor);
		if (!sgl)
			return NULL;
		for (SourceGroupList::iterator iter = sgl->begin (); iter != sgl->end (); iter++) {
			if (*iter == sgs)
				return & (*iter);
		}
		return NULL;
	}

	SourceGroupState* FindSourceGroupState (int32_t interface, Ipv4Address neighbor, const Ipv4Address source, const Ipv4Address group) {
		SourceGroupPair sgp (source,group);
		return FindSourceGroupState (interface, neighbor, sgp);
	}

	void InsertSourceGroupState (int32_t interface, Ipv4Address neighbor, SourceGroupState ns) {
		if (!FindSourceGroupState (interface, neighbor, ns)) {
			m_IfaceSourceGroup.find (WiredEquivalentInterface(interface,neighbor))->second.push_back (ns);
			//NeighborhoodStatus *status = FindNeighborhoodStatus (interface);
			SourceGroupState *sgs = FindSourceGroupState (interface, neighbor, ns);
			sgs->upstream = NULL;
			sgs->LocalMembership = Local_NoInfo;
			sgs->PruneState = Prune_NoInfo;
			sgs->AssertState = Assert_NoInfo;
			if (IsUpstream(interface, neighbor,sgs->SGPair)){
				sgs->upstream = new UpstreamState;
			}
		}
	}


	void InsertSourceGroupState (int32_t interface, Ipv4Address neighbor, SourceGroupPair sgp) {
		SourceGroupState *sgState = FindSourceGroupState (interface, neighbor, sgp);
			if (sgState == NULL) {
				SourceGroupState sgs (sgp);
				sgs.SGPair.nextMulticastAddr = neighbor;
				sgs.LocalMembership = Local_NoInfo;
				sgs.PruneState = Prune_NoInfo;
				sgs.AssertState = Assert_NoInfo;
				sgs.upstream = NULL;
				WiredEquivalentInterface key(interface,neighbor);
				SourceGroupList sgl;
				std::pair<WiredEquivalentInterface,SourceGroupList> k_pair(key,sgl);
				m_IfaceSourceGroup.insert(k_pair);
				NS_ASSERT(m_IfaceSourceGroup.find(key) != m_IfaceSourceGroup.end());
				m_IfaceSourceGroup.find(key)->second.push_back(sgs);
				NS_ASSERT(m_IfaceSourceGroup.find(key)->second.size() > 0);
				sgState = FindSourceGroupState (interface, neighbor, sgp);
				if(IsUpstream(interface,neighbor,sgp))
					sgState->upstream = new UpstreamState;
				}
		}


	void EraseSourceGroupState (int32_t interface, Ipv4Address neighbor, const SourceGroupState &ns) {
		SourceGroupList *sgl = FindSourceGroupList (interface, neighbor);
		if (!sgl)
			return;
		for (SourceGroupList::iterator iter = sgl->begin (); iter != sgl->end (); iter++) {
			if (*iter == ns) {
				sgl->erase (iter++);
			}
		}
	}

	void ChangeSourceGroupState (int32_t oldinterface, Ipv4Address oldneighbor, int32_t newinterface, Ipv4Address newneighbor, const SourceGroupState &ns) {
		SourceGroupList *sgl_old = FindSourceGroupList (oldinterface, oldneighbor);
		SourceGroupList *sgl_new = FindSourceGroupList (newinterface, newneighbor);
		if (!sgl_old || !sgl_new)
			return;
		SourceGroupState *sg1,*sg2;
		sg1=FindSourceGroupState(oldinterface, oldneighbor, ns.SGPair);
		sg2=FindSourceGroupState(newinterface, newneighbor, ns.SGPair);
		for (SourceGroupList::iterator iter = sgl_old->begin (); iter != sgl_old->end (); iter++) {
			if (iter->SGPair == ns.SGPair) {
				InsertSourceGroupState(newinterface, newneighbor, ns.SGPair);
				if(IsUpstream(newinterface, newneighbor, ns.SGPair)){
					sg2=FindSourceGroupState(newinterface, newneighbor, ns.SGPair);
					sg2->upstream = new UpstreamState;
				}
				sgl_old->erase (iter++);
			}
		}
		sg1=FindSourceGroupState(oldinterface, oldneighbor, ns.SGPair);
		sg2=FindSourceGroupState(newinterface, newneighbor, ns.SGPair);
		sg1=sg2;
	}

	NeighborhoodStatus* FindNeighborhoodStatus (int32_t interface) {
		std::map<int32_t, NeighborhoodStatus>::iterator iter =
				m_IfaceNeighbors.find (interface);
		return (iter == m_IfaceNeighbors.end () ? NULL : & (iter->second));
	}

	void InsertNeighborhoodStatus (const int32_t interface) {
		if (!FindNeighborhoodStatus (interface)) {
			NeighborhoodStatus *is = new NeighborhoodStatus;
			m_IfaceNeighbors.insert (std::pair<int32_t, NeighborhoodStatus> (interface, *is));
		}
	}

	void EraseNeighborhoodStatus (const int32_t interface) {
		m_IfaceNeighbors.erase (interface);
	}

	NeighborState* FindNeighborState (int32_t interface, const NeighborState ns) {
		NeighborhoodStatus *status = FindNeighborhoodStatus (interface);
		if (!status)
			return NULL;
		NeighborList *list = &status->neighbors;
		for (NeighborList::iterator iter = list->begin (); iter != list->end (); iter++) {
			NeighborState *no = & (*iter);
			if (*iter == ns)
				return & (*iter);
		}
		return NULL;
	}

	void InsertNeighborState(int32_t interface, const NeighborState ns) {
		if (!FindNeighborState(interface, ns)) {
			NeighborhoodStatus *nstatus = FindNeighborhoodStatus(interface);
			NS_ASSERT(nstatus!=NULL);
			nstatus->neighbors.push_back(ns);
			NeighborState *neighbor = FindNeighborState(interface, ns);
			NS_ASSERT(neighbor!=NULL);
			if(neighbor->neigborNLT.IsRunning())
				neighbor->neigborNLT.Cancel();
			neighbor->neighborCreation = Simulator::Now();
			neighbor->neighborTimeout = neighbor->neighborCreation;
			neighbor->neighborTimeoutB = true;
		}
	}

	void EraseNeighborState (int32_t interface, const NeighborState &ns) {
		FindNeighborhoodStatus (interface)->neighbors.remove (ns);
	}

	void EraseNeighborState (const int32_t interface) {
		std::map<int32_t, NeighborhoodStatus>::iterator iter =
				m_IfaceNeighbors.find (interface);
		if (iter != m_IfaceNeighbors.end ())
			m_IfaceNeighbors.erase (iter);
	}

	void SetStateRefreshCapable (int32_t interface, bool state) {
		NeighborhoodStatus *in = FindNeighborhoodStatus (interface);
		in->stateRefreshCapable = state;
	}

	void SetLANDelayEnabled (int32_t interface, bool state) {
		NeighborhoodStatus *in = FindNeighborhoodStatus (interface);
		in->LANDelayEnabled = state;
	}

	void SetPropagationDelay (int32_t interface, Time delay) {
		NeighborhoodStatus *in = FindNeighborhoodStatus (interface);
		in->propagationDelay = delay;
	}

	void SetOverrideInterval (int32_t interface, Time interval) {
		NeighborhoodStatus *in = FindNeighborhoodStatus (interface);
		in->overrideInterval = interval;
	}

	void GetPrinterList (std::string string, std::set<WiredEquivalentInterface > resB){
		std::cout<<string<<": ";
		for (std::set<WiredEquivalentInterface >::iterator iter = resB.begin (); iter!= resB.end (); iter++){
			std::cout<<"("<<iter->first<<","<<iter->second<<") ";
		}
		std::cout<< (resB.begin () == resB.end ()?"-":".")<<"\n";
	}

	///
	/// \brief The most important macros are those defining the outgoing
	///  interface list (or "olist") for the relevant state.
	///  immediate_olist (S,G) = pim_nbrs (-) prunes (S,G) (+) ( pim_include (*,G) (-) pim_exclude (S,G) ) (+)
	///              pim_include (S,G) (-) lost_assert (S,G) (-) boundary (G)
	/// \param source Source IPv4 address
	/// \param group Multicast group IPv4 address
	///
	std::set<WiredEquivalentInterface > immediate_olist (Ipv4Address source, Ipv4Address group) {

		std::set<WiredEquivalentInterface > resA;
		/// The set pim_nbrs is the set of all interfaces on which the router has at least one active PIM neighbor.
		std::set<WiredEquivalentInterface > pim_nbrz = pim_nbrs ();
		GetPrinterList ("pim_nbrz",pim_nbrz);
		/// prunes (S,G) = {all interfaces I such that DownstreamPState (S,G,I) is in Pruned state}
		std::set<WiredEquivalentInterface > prunez = prunes (source, group);
		GetPrinterList ("prunez",prunez);
		/// pim_nbrs * (-)* prunes (S,G)
		std::set_difference (pim_nbrz.begin (), pim_nbrz.end (), prunez.begin (), prunez.end (),
				 std::inserter (resA, resA.end ()));
		GetPrinterList ("pim_nbrs * (-)* prunes (S,G)",resA);
		std::set<WiredEquivalentInterface > resB;
		/// pim_include (*,G) = {all interfaces I such that: local_receiver_include (*,G,I)}
		std::set<WiredEquivalentInterface > inc = pim_include (Ipv4Address::GetAny (), group);
		GetPrinterList ("pim_include (*,G)",inc);
		/// pim_exclude (S,G) = {all interfaces I such that: local_receiver_exclude (S,G,I)}
		std::set<WiredEquivalentInterface > exc = pim_exclude (source, group);
		GetPrinterList ("pim_exclude (S,G)",exc);
		/// pim_include (*,G) * (-)* pim_exclude (S,G)
		std::set_difference (inc.begin (), inc.end (), exc.begin (), exc.end (), std::inserter (resB, resB.end ()));
		GetPrinterList ("pim_include (*,G) * (-)* pim_exclude (S,G)",resB);
		std::set<WiredEquivalentInterface > result;
		/// pim_nbrs (-) prunes (S,G) * (+)* (pim_include (*,G) (-) pim_exclude (S,G) )
		std::set_union (resA.begin (), resA.end (), resB.begin (), resB.end (), std::inserter (result, result.end ()));
		GetPrinterList ("pim_nbrs (-) prunes (S,G) * (+)* (pim_include (*,G) (-) pim_exclude (S,G))",result);
		/// pim_include (S,G) = {all interfaces I such that: local_receiver_include (S,G,I)}
		std::set<WiredEquivalentInterface > incC = pim_include (source, group);
		GetPrinterList ("pim_include (S,G)",incC);
		/// pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) * (+)* pim_include (S,G)
		std::set_union (result.begin (), result.end (), incC.begin (), incC.end (), std::inserter (resA, resA.end ()));
		GetPrinterList ("pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) * (+)* pim_include (S,G)",resA);

		std::set<WiredEquivalentInterface > lostC = lost_assert (source, group);
		GetPrinterList ("lost_assert",lostC);
		/// pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) (+) pim_include (S,G) * (-)* lost_assert (S,G)
		std::set_difference (resA.begin (), resA.end (), lostC.begin (), lostC.end (),std::inserter (resB, resB.end ()));
		GetPrinterList ("pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) (+) pim_include (S,G) * (-)* lost_assert (S,G)",resB);
		std::set<WiredEquivalentInterface > boundC = boundary (group);
		GetPrinterList ("boundary",boundC);
		std::set<WiredEquivalentInterface > resC;
		/// pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) (+) pim_include (S,G) (-) lost_assert (S,G) * (-)* boundary (G)
		std::set_difference (resB.begin (), resB.end (), boundC.begin (), boundC.end (),std::inserter (resC, resC.end ()));
		GetPrinterList ("pim_nbrs (-) prunes (S,G) (+) (pim_include (*,G) (-) pim_exclude (S,G) ) (+) pim_include (S,G) (-) lost_assert (S,G) * (-)* boundary (G)",resC);
		std::set<WiredEquivalentInterface > incCprime = incC;
		for(std::set<WiredEquivalentInterface >::iterator citer = incC.begin(); citer != incC.end() ; citer++){
			for(std::set<WiredEquivalentInterface >::iterator iter = resC.begin(); iter != resC.end() ; iter++){
				if(iter->first == citer->first) {
					incCprime.erase(*citer);
					break;
				}
			}
		}
		result.clear();
		std::set_difference (resC.begin (), resC.end (), incC.begin (), incC.end (),std::inserter (result, result.end ()));
		GetPrinterList ("removing duplicates A: ",result);
		resC.clear();
		if(incCprime.size()){
			std::set_union (result.begin (), result.end (), incCprime.begin (), incCprime.end (), std::inserter (resC, resC.end ()));
			GetPrinterList ("removing duplicates B: ",resC);
			return resC;
		}
		else
			return result;
	}

	void SourceDirectlyConnected (SourceGroupPair &sgp);
	void SourceNoDirectlyConnected (SourceGroupPair &sgp);
	/// Basically RPF' is the RPF neighbor toward a source
	/// unless a PIM-DM Assert has overridden the normal choice of neighbor.

	void RPF_primeChanges (SourceGroupPair &sgp, Ipv4Address destination);

//	void RPF_Changes (SourceGroupPair &sgp, int32_t oldInterface, int32_t newInterface);
	void RPF_Changes(SourceGroupPair &sgp, int32_t oldInterface, Ipv4Address oldGateway, int32_t newInterface, Ipv4Address newGateway);

	void RPFCheck (SourceGroupPair sgp, int32_t interface, Ptr<Ipv4Route> rpf_route);
	void RPFCheckAll ();

	void olistCheck (SourceGroupPair &sgp, std::set<WiredEquivalentInterface > &list);
	void olistEmpty (SourceGroupPair &sgp);
	void olistFull (SourceGroupPair &sgp);

	/// \brief The outgoing interfaces except the RPF_interface.
	///
	/// \param source Source IPv4 address
	/// \param group Multicast group IPv4 address
	std::set<WiredEquivalentInterface > olist (Ipv4Address source, Ipv4Address group) {
		std::set<WiredEquivalentInterface > _olist = immediate_olist (source, group);
		GetPrinterList ("olist", _olist);
		_olist.erase (RPF_interface(source));
		GetPrinterList ("olist-RPF interface",_olist);
		return _olist;
	}

	/// \brief RPF interface towards the source S as indicated by the MRIB.
	/// \param source Source IPv4 address
	WiredEquivalentInterface RPF_interface (Ipv4Address source);

	/// \brief There are receivers for the given SourceGroup pair.
	/// \param sgp source-group pair.
	/// \return True if there are receivers interested in, false otherwise.
	bool GetLocalReceiver(SourceGroupPair sgp){
		return m_LocalReceiver.find(sgp) != m_LocalReceiver.end();
	}

	/// \brief There are receivers for the given SourceGroup pair on that interface.
	/// \param sgp source-group pair.
	/// \param interface node interface
	/// \return True if there are receivers on the particular interface that are interested in, false otherwise.
	bool GetLocalReceiverInterface(SourceGroupPair sgp, int32_t interface){
		return GetLocalReceiver(sgp) && m_LocalReceiver.find(sgp)->second.find(interface) != m_LocalReceiver.find(sgp)->second.end();
	}

	/*
	 * The macro local_receiver_include (S,G,I) is true if the IGMP module or
	 * other local membership mechanism has determined that there are local
	 * members on interface I that seek to receive traffic sent specifically by S to G.
	 */
	bool local_receiver_include (Ipv4Address source, Ipv4Address group, int32_t interface) {
		if (group==Ipv4Address::GetAny () || source == Ipv4Address::GetAny()){//no group or no source: no way to identify members
			return false;
		}
		SourceGroupPair sgp (source,group);
		return (GetLocalReceiver(sgp) && GetLocalReceiverInterface(sgp, interface));
	}

	//
	///The interfaces to which traffic might be forwarded because
	//  of hosts that are local members on those interfaces.
	//
	//  pim_include (*,G) = {all interfaces I such that: local_receiver_include (*,G,I)}
	//  pim_include (S,G) = {all interfaces I such that: local_receiver_include (S,G,I)}
	std::set<WiredEquivalentInterface > pim_include (Ipv4Address source, Ipv4Address group) {
		std::set<WiredEquivalentInterface > include;
		SourceGroupPair sgp (source,group);
		for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
			if (IsLoopInterface (i))continue;
			if (local_receiver_include (source, group, i)) {
				WiredEquivalentInterface n_include (i,GetLocalAddress(i));
				include.insert (n_include);
			}
		}
		return include;
	}

	bool seek_traffic_from (Ipv4Address source, Ipv4Address group,int32_t interface) {
		Ipv4Address nexthop = GetNextHop(source);
		SourceGroupPair sgp (source,group);
		return (FindSourceGroupState (interface, nexthop, sgp) == NULL?true:! (FindSourceGroupState (interface, nexthop, sgp)->members));
	}

	// Local members for a (source,group) pair.
	// True if local_receiver_include (*,G,I) is true
	// but none of the local members seek to receive traffic from S.
	bool local_receiver_exclude (Ipv4Address source, Ipv4Address group, int32_t interface) {
		return local_receiver_include (Ipv4Address::GetAny (), group, interface)
				&& seek_traffic_from (source,group,interface);
	}

	/// The interfaces to which traffic might not be forwarded because of hosts that are not local members on those interfaces.
	///  pim_exclude (S,G) = {all interfaces I such that: local_receiver_exclude (S,G,I)}
	std::set<WiredEquivalentInterface > pim_exclude (Ipv4Address source, Ipv4Address group) {
		std::set<WiredEquivalentInterface > exclude;
		for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
			if (IsLoopInterface (i))continue;
			if (local_receiver_exclude (source, group, i)) {
				WiredEquivalentInterface n_exclude(i, GetLocalAddress(i));
				exclude.insert (n_exclude);
			}
		}
		return exclude;
	}

	bool IsLoopInterface (int32_t interface){
		Ipv4Address loopback ("127.0.0.1");
		Ipv4Address addr = m_ipv4->GetAddress (interface, 0).GetLocal ();
		return (addr==loopback);
	}

	/*
	 * All interfaces on which the router has at least one active PIM neighbor.
	 */
	std::set<WiredEquivalentInterface > pim_nbrs (void) {
		std::set<WiredEquivalentInterface > pimNbrs;
		for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
			if (IsLoopInterface (i) || m_IfaceNeighbors.find(i) == m_IfaceNeighbors.end())continue;
			for(NeighborList::iterator iter = m_IfaceNeighbors.find(i)->second.neighbors.begin();
					iter != m_IfaceNeighbors.find(i)->second.neighbors.end(); iter++)
				pimNbrs.insert(WiredEquivalentInterface (i, iter->neighborIfaceAddr));
		}
		return pimNbrs;
	}

	/*
	 * The set of all interfaces on which the router has received Prune (S,G) messages:
	 *   prunes (S,G) = {all interfaces I such that DownstreamPState (S,G,I) is in Pruned state}
	 */
	std::set<WiredEquivalentInterface > prunes (Ipv4Address source, Ipv4Address group) {
		std::set<WiredEquivalentInterface > prune;
		SourceGroupPair sgp (source,group);
		for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
			if (IsLoopInterface (i))continue;
			for(std::map<WiredEquivalentInterface, SourceGroupList>::iterator iter = m_IfaceSourceGroup.begin();
					iter != m_IfaceSourceGroup.end(); iter++){
				if(i!=iter->first.first) continue;
				SourceGroupState *sgState = FindSourceGroupState (iter->first.first, iter->first.second, sgp);///TODO continue after replacing SGS
				if (!sgState) continue;
				if ( IsDownstream(iter->first.first, iter->first.second, source) && sgState->PruneState == Prune_Pruned) {
					prune.insert (iter->first);
				}
			}
		}
		return prune;
	}

	/* The set lost_assert (S,G) is the set of all interfaces on which the
	 *  router has lost an (S,G) Assert.
	 *  lost_assert (S,G) = {all interfaces I such that
	 *            lost_assert (S,G,I) == TRUE}
	 *
	 */
	std::set<WiredEquivalentInterface > lost_assert (Ipv4Address source, Ipv4Address group) {
		std::set<WiredEquivalentInterface > set;
		SourceGroupPair sgp (source, group);
		for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
			if (IsLoopInterface (i))continue;
			for(std::map<WiredEquivalentInterface, SourceGroupList>::iterator iter = m_IfaceSourceGroup.begin();
					iter != m_IfaceSourceGroup.end(); iter++){
				SourceGroupState *sgState = FindSourceGroupState (i, iter->first.second, sgp);///TODO continue after replacing SGS
				if (!sgState) continue;
				if (lost_assert (source, group, i, iter->first.second))
					set.insert (iter->first);
			}
		}
		return set;
	}

	/*
	 * True if the node has lost an (S,G) Assert on that interface.
	 */
	bool lost_assert (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address neighbor) {
		Ipv4Address assertWinner = AssertWinner (source, group, interface, neighbor);
		bool result = assertWinner != Ipv4Address::GetAny ();
		result = result && assertWinner != GetLocalAddress (interface);
		result = result && AssertWinnerMetric (source, group, interface, neighbor) > spt_assert_metric (source, interface);
		return result;
	}

	//AssertWinner (S,G,I) defaults to NULL -> ANY
	Ipv4Address AssertWinner (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address neighbor) {
		SourceGroupPair sgp (source, group);
		SourceGroupState *sgState = FindSourceGroupState (interface, neighbor, sgp);
		sgState = FindSourceGroupState (interface, neighbor, source, group);
		return (sgState==NULL) ? Ipv4Address::GetAny () : sgState->AssertWinner.IPAddress;
	}

	struct AssertMetric AssertWinnerMetric (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address neighbor) {
		SourceGroupState *sgState = FindSourceGroupState (interface, neighbor, source, group);
		return (sgState == NULL || sgState->AssertState == Assert_NoInfo) ? infinite_assert_metric () : sgState->AssertWinner;
	}

	bool boundary (int32_t interface, Ipv4Address group){
		//TODO administratively scoped boundary
		return false;
	}

	/*
	 * boundary (G) = {all interfaces I with an administratively scoped boundary for group G}
	 */
	std::set<WiredEquivalentInterface > boundary (Ipv4Address G) {
		std::set<WiredEquivalentInterface > bound;
		for (int32_t i = 0; i < m_ipv4->GetNInterfaces (); i++) {
			if (IsLoopInterface (i))continue;
			if (boundary (i,G)){ //administratively scoped boundary
				WiredEquivalentInterface b_pair (i ,GetLocalAddress(i));
				bound.insert(b_pair); //TODO: fix this with the right value
			}
		}
		return bound;
	}

	//The macro I_Am_Assert_loser (S, G, I) is true if the Assert state
	//  machine (in Section 4.6) for (S,G) on interface I is in the "I am
	//  Assert Loser" state.
	Ipv4Address RPF_prime (Ipv4Address source, Ipv4Address group) {
		WiredEquivalentInterface wei = RPF_interface (source);
		if (I_Am_Assert_loser (source, group, wei.first, wei.second)) {
			return AssertWinner (source, group, wei.first, wei.second);
		} else {
			return wei.second;
		}
	}

	bool I_Am_Assert_loser (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address nexthop) {
		SourceGroupState *sgState = FindSourceGroupState (interface, nexthop, source, group);
		return (sgState != NULL?sgState->AssertState == Assert_Loser: false);
	}

	Ipv4Address RPF_prime (SourceGroupPair sgp) {
		return RPF_prime (sgp.sourceMulticastAddr,sgp.groupMulticastAddr);
	}

	Ipv4Address RPF_prime (Ipv4Address source) {
		return GetNextHop (source);
	}

	void CouldAssertCheck (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address destination, bool couldAssert);

	bool CouldAssert (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address neighbor) {
		WiredEquivalentInterface rpfCheck = RPF_interface (source);
		bool couldAssert = rpfCheck.first != interface;
		couldAssert = couldAssert || rpfCheck.second != neighbor;
		return couldAssert;
	}

	struct AssertMetric spt_assert_metric (Ipv4Address source, int32_t interface) {
		struct AssertMetric assertMetric (GetMetricPreference (interface),
				GetRouteMetric (interface,source), GetLocalAddress (interface));
		return assertMetric;
	}

	struct AssertMetric infinite_assert_metric (){
		struct AssertMetric assertMetric (0xFFFFFFFF, 0xFFFFFFFF, Ipv4Address ("255.255.255.255"));
		return assertMetric;
	}

	struct AssertMetric my_assert_metric (Ipv4Address source, Ipv4Address group, int32_t interface, Ipv4Address neighbor) {
		if (CouldAssert (source, group, interface, neighbor)) {
			return spt_assert_metric (source, interface);
		} else {
			return infinite_assert_metric ();
		}
	}

	//StateRefreshRateLimit (S,G) is TRUE if the time elapsed since the last received StateRefresh (S,G)
	//	is less than the configured RefreshLimitInterval.
	bool StateRefreshRateLimit (Ipv4Address source, Ipv4Address group){
		WiredEquivalentInterface wei = RPF_interface (source);
		return FindSourceGroupState (wei.first, wei.second, source, group)->lastStateRefresh.GetSeconds () < RefreshInterval;
	}

	bool StateRefreshCapable (int32_t interface){
		return FindNeighborhoodStatus (interface)->stateRefreshCapable;
	}

	void SetPruneState (int32_t interface, Ipv4Address neighbor, SourceGroupPair sgp, PruneState state){
		SourceGroupState *sgState = FindSourceGroupState (interface, neighbor, sgp);
		sgState->PruneState = state;
	}
};

struct RelyTag : public Tag
{
	uint8_t m_rely;
	RelyTag (uint8_t value = 0) : Tag(), m_rely(value) {}

  static TypeId GetTypeId()
  {
	  static TypeId tid = TypeId ("ns3::RelyTag").SetParent<Tag>();
	  return tid;
  }

  TypeId GetInstanceTypeId (void) const
  {
	  return GetTypeId();
  }

  uint32_t GetSerializedSize (void) const
  {
	  return sizeof(m_rely);
  }

  void Serialize (TagBuffer i) const
  {
	  i.WriteU8(m_rely);
  }

  void Deserialize (TagBuffer i)
  {
	  m_rely = i.ReadU8();
  }

  void Print (std::ostream &os) const
  {
	  os<<" RelyTag "<< m_rely;
  }

};

}
}// namespace pimdm, ns3
#endif
