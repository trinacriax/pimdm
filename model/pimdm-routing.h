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

/// \brief	This header file declares and defines internal state of an PIM-DM node.

#ifndef __PIM_DM_ROUTING_H__
#define __PIM_DM_ROUTING_H__

/// Timer Name: Hello Timer (HT). Periodic interval for hello messages.
#define Hello_Period 30
/// Timer Name: Hello Timer (HT). Random interval for initial Hello message on bootup or triggered Hello message to a rebooting neighbor.
#define Triggered_Hello_Delay 5
/// The Hold Time in the Hello Message should be set to a value that can
///   reasonably be expected to keep the Hello active until a new Hello
///   message is received.  On most links, this will be 3.5 times the value
///   of Hello_Period.
#define Hold_Time_Default (3.5*Hello_Period) //seconds
/// Timer Name: Assert Timer (AT(S,G,I)). Period after last assert before assert state is timed out.
#define Assert_Time 180
/// Timer Name: Graft Retry Timer (GRT(S,G)). In the absence of receipt of a GraftAck message, the time before retransmission of a Graft message.
#define Graft_Retry_Period 3
/// Used to prevent Prune storms on a LAN.
#define t_limit 210
/// Timer Name: Upstream Override Timer (OT(S,G)).
#define t_short t_override
#define t_shorter 2
/// Timer Name: Source Active Timer (SAT(S,G)).
///   Period of time after receiving a multicast message a directly
///   attached router will continue to send State Refresh messages.
#define SourceLifetime 210
/// Timer Name: State Refresh Timer (SRT(S,G)).
///   Interval between successive state refresh messages.
#define RefreshInterval 60
#define StateRefreshInterval RefreshInterval
/// If all routers on a LAN are using the LAN Prune Delay option, the Override_Interval (OI(I)) MUST be set to the
///   largest value on the LAN.  Otherwise, the Override_Interval (OI(I)) MUST be set to 2.5 seconds.
#define Override_Interval 2.5
// The J/P_Override_Interval is the sum of the interface's
//	 Override_Interval (OI(I)) and Propagation_Delay (PD(I)).  If all
//	 routers on a LAN are using the LAN Prune Delay option, both
//	 parameters MUST be set to the largest value on the LAN.  Otherwise,
//	 the Override_Interval (OI(I)) MUST be set to 2.5 seconds, and the
//	 Propagation_Delay (PD(I)) MUST be set to 0.5 seconds.
#define Propagation_Delay 0.5
//  The number of seconds a receiving PIM-DM router MUST keep a Prune
//     state alive, unless removed by a Join or Graft message.  If the
//     Hold Time is '0xffff', the receiver MUST NOT remove the Prune state
//     unless a corresponding Join or Graft message is received.  The Hold
//     Time is ignored in Join messages.
#define PruneHoldTime 0xffff
/// Threshold(I) returns the minimum TTL that a packet must have before it can be transmitted on interface I. TODO what is it?
#define Threshold(uint32_t) 2 //TODO check what is it
//  The number of seconds a receiving PIM-DM router MUST keep a Prune
//     state alive, unless removed by a Join or Graft message.  If the
//     Hold Time is '0xffff', the receiver MUST NOT remove the Prune state
//     unless a corresponding Join or Graft message is received.  The Hold
//     Time is ignored in Join messages.
#define PruneHoldTime 0xffff
//If all routers on a LAN support the LAN Prune Delay option, then the
//   PIM routers on that LAN will use the values received to adjust their
//   J/P_Override_Interval on that interface and the interface is LAN
//   Delay Enabled.  Briefly, to avoid synchronization of Prune Override
//   (Join) messages when multiple downstream routers share a multi-access
//   link, sending of these messages is delayed by a small random amount
//   of time.  The period of randomization is configurable and has a
//   default value of 3 seconds.
#define JoinDelay 3 //Prune override
#define ALL_PIM_ROUTERS "224.0.0.13"
#define PIM_PORT_NUMBER 703 //IANA Unassigned

#include "ns3/test.h"
#include "pimdm-structure.h"
#include "pimdm-packet.h"

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

#include <vector>
#include <map>
#include <set>

namespace ns3 {
namespace pimdm {

struct RoutingMulticastTable {
	Ipv4Address source; ///< source destination
	Ipv4Address nextAddr; ///< next hop
	uint32_t route_metric; ///< route metric
	uint32_t interface; ///< interface to source
	uint32_t metricPreference;///< Metric Preference. The preference value assigned to the unicast routing protocol that provided the route to the source.
	RoutingMulticastTable() : // default values
		source(), nextAddr(), route_metric(0), interface(0), metricPreference(0) {
	}
	;
};

/// This class encapsulates all data structures needed for maintaining internal state of an PIM_DM node.
class MulticastRoutingProtocol: public Ipv4RoutingProtocol {
	//  friend class;
private:
	uint32_t m_mainInterface; ///< Node main interface.
	Ipv4Address m_mainAddress; ///< Main address on the main interface.

	///\name Protocol fields;
	//\{
	std::map<uint32_t, NeighborhoodStatus> m_IfaceNeighbors; ///< Information on interface and neighbors (RFC 3973, section 4.1.1).
	///TIB - Tree Information Base
	std::map<uint32_t, SourceGroupList> m_IfaceSourceGroup; ///< List of (S,G) pair state (RFC 3973, section 4.1.2).

	///pim ENABLED INTERFACES
	std::map<uint32_t, bool> m_IfacePimEnabled; //TODO, right now all interfaces are pim enabled.
	Time m_helloTime; ///< Hello Time
	uint16_t m_helloHoldTime; ///< Default hello hold time
	uint32_t m_generationID;
	bool m_stopTx;
	//}
	std::set<uint32_t> m_interfaceExclusions;

	///\name Fields for each interface
	//\{
	Ptr<Ipv4StaticRouting> m_routingTableAssociation;

	/**
	 * This is the multicast topology table, which is typically derived
	 * from the unicast routing table, or from routing protocols such as
	 * MBGP that carry multicast-specific topology information.  PIM-DM
	 * uses the MRIB to make decisions regarding RPF interfaces.
	 */
	std::map<Ipv4Address, RoutingMulticastTable> m_mrib; ///< Multicast Routing Information Base (MRIB)

	/// IP protocol
	Ptr<Ipv4> m_ipv4;

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

	TracedCallback <const PIMHeader &> m_rxPacketTrace;
	TracedCallback <const PIMHeader &> m_txPacketTrace;

	TracedCallback<uint32_t> m_routingTableChanged;

protected:
	virtual void DoStart(void);

public:
	static TypeId GetTypeId(void);

	MulticastRoutingProtocol();
	virtual ~MulticastRoutingProtocol();

	void SetMainInterface(uint32_t interface);
	uint32_t GetMainInterface() {
		return m_mainInterface;
	}

	void SetInterfaceExclusions(std::set<uint32_t> exceptions);
	std::set<uint32_t> GetInterfaceExclusions() const {
		return m_interfaceExclusions;
	}
	/**
	 * Return the list of routing table entries discovered by OLSR
	 **/
	std::vector<RoutingMulticastTable> GetRoutingTableEntries() const;

	void register_member(Ipv4Address source, Ipv4Address group, uint32_t interface) {
		SourceGroupPair sgp(source,group);
		SourceGroupState *sgState = FindSourceGroupState(interface,sgp);
		if(sgState==NULL){
			InsertSourceGroupState(interface,*sgState);
		}
		sgState = FindSourceGroupState(interface,sgp);
		sgState->members = true;
		//no local member registered
	}


private:
	void Clear();
	uint32_t GetSize() const {
		return m_mrib.size();
	}

	void RemoveEntry(const Ipv4Address &dest);
	void AddEntry(const Ipv4Address &dest, const Ipv4Address &next,uint32_t interface, uint32_t distance);
	void AddEntry(const Ipv4Address &dest, const Ipv4Address &next,const Ipv4Address &interfaceAddress, uint32_t distance);
	bool Lookup(const Ipv4Address &dest, RoutingMulticastTable &outEntry) const;
	bool FindSendEntry(const RoutingMulticastTable &entry,RoutingMulticastTable &outEntry) const;
	Ipv4Address GetLocalAddress(uint32_t interface);

	// From Ipv4RoutingProtocol
	virtual Ptr<Ipv4Route> RouteOutput(Ptr<Packet> p, const Ipv4Header &header,Ptr<NetDevice> oif, Socket::SocketErrno &sockerr);
	// From Ipv4RoutingProtocol
	virtual bool RouteInput(Ptr<const Packet> p, const Ipv4Header &header,Ptr<const NetDevice> idev, UnicastForwardCallback ucb,
			MulticastForwardCallback mcb, LocalDeliverCallback lcb,ErrorCallback ecb);
	// From Ipv4RoutingProtocol
	virtual void NotifyInterfaceUp(uint32_t interface);
	// From Ipv4RoutingProtocol
	virtual void NotifyInterfaceDown(uint32_t interface);
	// From Ipv4RoutingProtocol
	virtual void NotifyAddAddress(uint32_t interface,Ipv4InterfaceAddress address);
	// From Ipv4RoutingProtocol
	virtual void NotifyRemoveAddress(uint32_t interface,Ipv4InterfaceAddress address);
	// From Ipv4RoutingProtocol
	virtual void SetIpv4(Ptr<Ipv4> ipv4);
	// From Ipv4RoutingProtocol
	virtual void PrintRoutingTable(Ptr<OutputStreamWrapper> stream) const;

	void DoDispose();

	void SetHelloHoldTime(uint16_t holdt){
		m_helloHoldTime = holdt;
	}

	uint16_t GetHelloHoldTime(){
		return m_helloHoldTime;
	}

	void SetGenerationID(uint32_t gid) {
		m_generationID = gid;
	}
	uint32_t GetGenerationID() {
		return m_generationID;
	}

	void SetStopTx() {
		m_stopTx = true;
	}

	void UnsetStopTx() {
		m_stopTx = false;
	}

	bool GetStopTx(){
		return m_stopTx;
	}

	///\name Fields for each interface
	/// Check that address is one of my interfaces
	bool IsMyOwnAddress(const Ipv4Address & a) const;

	bool IsValidSG(uint32_t interface, const Ipv4Address & source,const Ipv4Address & group);

	bool UsesNonPimDmOutgoingInterface(const Ipv4RoutingTableEntry &route);

	///< Randomized delay to prevent response implosion when sending a join message  to override someone else's prune
	/// t_override is a random value between 0 and the interface's Override_Interval (OI(I)).
	/// If all routers on a LAN are using the LAN Prune Delay option, the Override_Interval (OI(I)) MUST be set to the
	/// largest value on the LAN.  Otherwise, the Override_Interval (OI(I)) MUST be set to 2.5 seconds.

	uint32_t t_override(uint32_t interface){
		return UniformVariable().GetValue(0, OverrideInterval(interface));
	}

	uint32_t OverrideInterval(uint32_t interface){
			NeighborhoodStatus *ns = FindNeighborhoodStatus(interface);
			bool LPDO = true;
			for(std::list<NeighborState>::iterator iter = ns->neighbors.begin(); iter!=ns->neighbors.end() && LPDO; iter++){
				LPDO = LPDO && (iter->neighborOverrideInterval.GetSeconds()>0);
				ns->overrideInterval = Max(ns->overrideInterval ,iter->neighborOverrideInterval);
			}
			return (LPDO?ns->overrideInterval.GetSeconds():Override_Interval);
	}

	PIMHeader::EncodedUnicast ForgeEncodedUnicast (Ipv4Address unicast){
			PIMHeader::EncodedUnicast egroup = {AF_IPv4, NATIVE_ENCODING, unicast};
			return egroup;
		}

	PIMHeader::EncodedGroup ForgeEncodedGroup(Ipv4Address group){
		PIMHeader::EncodedGroup egroup = {AF_IPv4, NATIVE_ENCODING, 0, 0, 0, IPV4_ADDRESS_SIZE, group};
		return egroup;
	}

	PIMHeader::EncodedSource ForgeEncodedSource(Ipv4Address source){
		PIMHeader::EncodedSource esource = {AF_IPv4, NATIVE_ENCODING, 0, 0, 0, 0, IPV4_ADDRESS_SIZE, source};
		return esource;
	}

	void ForgeHeaderMessage(enum PIMType type, PIMHeader &msg);
	void ForgeHelloMessage(uint32_t interface, PIMHeader &msg);
	void ForgeHelloMessageHoldTime (uint32_t interface, PIMHeader &msg);
	void ForgeHelloMessageLANPD (uint32_t interface, PIMHeader &msg);
	void ForgeHelloMessageGenID (uint32_t interface, PIMHeader &msg);
	void ForgeHelloMessageStateRefresh (uint32_t interface, PIMHeader &msg);

	void ForgePruneMessage(uint32_t interface, PIMHeader &msg);
	void ForgeAssertMessage (uint32_t interface, PIMHeader &msg);

	void AddMulticastGroupEntry(PIMHeader &msg,PIMHeader::MulticastGroupEntry &entry);
	void CreateMulticastGroupEntry(PIMHeader &msg,PIMHeader::MulticastGroupEntry m_entry,PIMHeader::EncodedGroup group);
	void AddMulticastGroupSourceJoin(PIMHeader::MulticastGroupEntry m_entry,PIMHeader::EncodedSource source);
	void AddMulticastGroupSourcePrune(PIMHeader::MulticastGroupEntry m_entry,PIMHeader::EncodedSource source);

	void SendHello(uint32_t interface);
	void SendNeighHello(uint32_t interface, Ipv4Address destination);
	void RecvHello(pimdm::PIMHeader::HelloMessage &hello, Ipv4Address sender,Ipv4Address receiver);

 	void ForgeStateRefresh (uint32_t interface, Ipv4Address target, SourceGroupPair &sgpair, PIMHeader &msg);
	void SendStateRefresh(uint32_t interface, PIMHeader &refresh);
	void SendStateRefreshPair(uint32_t interface, Ipv4Address target,SourceGroupPair &sgpair);
	void RecvStateRefresh(PIMHeader::StateRefreshMessage &refresh,Ipv4Address sender, Ipv4Address receiver);
	void ForwardingStateRefresh(PIMHeader::StateRefreshMessage &refresh,Ipv4Address sender, Ipv4Address receiver);

	void RecvJP(PIMHeader::JoinPruneMessage &jp, Ipv4Address sender,Ipv4Address receiver);

	void RecvJoin(PIMHeader::JoinPruneMessage &jp,const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group, uint32_t &interface);
	void RecvJoinUpstream(PIMHeader::JoinPruneMessage &jp, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group, uint32_t &interface);
	void RecvJoinDownstream(PIMHeader::JoinPruneMessage &jp,const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group, uint32_t &interface);

	void RecvPrune(PIMHeader::JoinPruneMessage &jp,const PIMHeader::EncodedSource &source,PIMHeader::EncodedGroup &group, uint32_t &interface);
	void RecvPruneUpstream (PIMHeader::JoinPruneMessage &jp, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group, uint32_t &interface);
	void RecvPruneDownstream (PIMHeader::JoinPruneMessage &jp, const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group, uint32_t &interface);

	void RecvAssert(PIMHeader::AssertMessage &assert, Ipv4Address sender,Ipv4Address receiver);

	void SendGraft(uint32_t interface, SourceGroupPair pair);
	void SendGraftUnicast(uint32_t interface, Ipv4Address target,SourceGroupPair pair);

	void RecvGraft(PIMHeader::GraftMessage &graft, Ipv4Address sender, Ipv4Address receiver);
	void RecvGraftDownstream(PIMHeader::GraftMessage &graft, Ipv4Address sender,const PIMHeader::EncodedSource &source, PIMHeader::EncodedGroup &group);

	void SendGraftAck(uint32_t interface, SourceGroupPair pair);
	void SendGraftAckUnicast(uint32_t interface, SourceGroupPair &pair, const Ipv4Address receiver);
	void RecvGraftAck(PIMHeader::GraftAckMessage &graftAck, Ipv4Address sender,Ipv4Address receiver);

	void SendPrune(uint32_t interface, SourceGroupPair &sgpair);
	void SendJoin(uint32_t interface, Ipv4Address target,SourceGroupPair &sgpair);

	void RecvData(Ptr<Packet> packet, Ipv4Address sender, Ipv4Address receiver);
	void SendBroadPacket(Ptr<Packet> packet, const PIMHeader &message);
	void SendPacket(Ptr<Packet> packet, const PIMHeader &message, Ipv4Address destination);
	void SendBroadPacketInterface (Ptr<Packet> packet, const PIMHeader &message, uint32_t interface);
	void SendBroadPacketInterface (Ptr<Packet> packet, uint32_t interface);
	//end
	void NeighborRestart(uint32_t interface);

	void RecvPimDm(Ptr<Socket> socket);

	void NeighborTimeout(uint32_t interface);
	/**
	 * Downstream Interface.
	 * All interfaces that are not the upstream interface, including the router itself.
	 */
	bool IsDownstream(uint32_t interface, SourceGroupPair sgpair);
	/**
	 * Upstream Interface.
	 * Interface toward the source of the datagram.  Also known as the RPF Interface.
	 */
	bool IsUpstream(uint32_t interface, SourceGroupPair sgpair);
	uint32_t GetRecevingInterface(Ipv4Address addr);
	uint32_t GetRecevingInterface(Ipv4InterfaceAddress interface);

	void SendPacket (Ptr<Packet> packet, const PIMMessageList &containedMessages);

	void HelloTimerExpire(uint32_t i);
	void OTTimerExpire(SourceGroupPair &sg);
	void GRTTimerExpire(SourceGroupPair &sgp);
	void PLTTimerExpire(SourceGroupPair &sgp);
	void ATTimerExpire (SourceGroupPair &sgp);
	void PPTTimerExpire(SourceGroupPair &sgp);
	void PTTimerExpire(SourceGroupPair &sgp);
//	void NLTTimerExpire (SourceGroupPair &sgp);
	void NLTTimerExpire (Ipv4Address neighborIfaceAddr, Ipv4Address receivingIfaceAddr);
	void SRTTimerExpire (SourceGroupPair &sgp);
	void SATTimerExpire (SourceGroupPair &sgp);

	SourceGroupList* FindSourceGroupList(uint32_t interface) {
		std::map<uint32_t, SourceGroupList>::iterator iter =
				m_IfaceSourceGroup.find(interface);
		return (iter == m_IfaceSourceGroup.end() ? NULL : &iter->second);
	}

	void InsertSourceGroupList(uint32_t interface) {
		std::map<uint32_t, SourceGroupList>::iterator iter =
				m_IfaceSourceGroup.find(interface);
		if (iter != m_IfaceSourceGroup.end())
			return;
		SourceGroupList sgl;
		m_IfaceSourceGroup.insert(
				std::pair<uint32_t, SourceGroupList>(interface, sgl));

	}

	void EraseSourceGroupList(uint32_t interface) {
		m_IfaceSourceGroup.erase(interface);
	}

	SourceGroupState* FindSourceGroupState(uint32_t interface,const SourceGroupState &sgs) {
		SourceGroupList *sgl = FindSourceGroupList(interface);
		if (!sgl)
			return NULL;
		for (SourceGroupList::iterator iter = sgl->begin(); iter != sgl->end(); iter++) {
			if (*iter == sgs)
				return &(*iter);
		}
		return NULL;
	}

	SourceGroupState* FindSourceGroupState(uint32_t interface,const SourceGroupPair &sgp) {
		SourceGroupList *sgl = FindSourceGroupList(interface);
		if (!sgl)
			return NULL;
		for (SourceGroupList::iterator iter = sgl->begin(); iter != sgl->end(); iter++) {
			if (iter->SGPair == sgp)
				return &(*iter);
		}
		return NULL;
	}
	SourceGroupState* FindSourceGroupState(uint32_t interface, const Ipv4Address source, const Ipv4Address group) {
		SourceGroupPair sgp(source,group);
		return FindSourceGroupState(RPF_interface(source),sgp);
	}

	void InsertSourceGroupState(uint32_t interface, const SourceGroupState &ns) {
		if (!FindSourceGroupState(interface, ns)) {
			m_IfaceSourceGroup.find(interface)->second.push_back(ns);
			//NeighborhoodStatus *status = FindNeighborhoodStatus(interface);
			SourceGroupState *sgs = FindSourceGroupState(interface, ns);
			sgs->SGLocalMembership = Local_NoInfo;
			sgs->SGPruneState = Prune_NoInfo;
			sgs->SGAssertState = Assert_NoInfo;
			if(RPF_interface(ns.SGPair.sourceIfaceAddr) == interface){
				UpstreamState us;
				sgs->upstream=&us;
				sgs->upstream->SGGraftPrune = GP_NoInfo;
			}
			//	  		sgs->SG_PPT.Cancel();
			//	  		sgs->SG_PPT.SetDelay(status->overrideInterval+status->propagationDelay);
			//	  		///sgs->SG_PPT.SetFunction (&MulticastRoutingProtocol::???, this);
			//	  		sgs->SG_PT.Cancel();
			//	  		///sgs->SG_PT.SetFunction (&MulticastRoutingProtocol::???, this);
			//	  		sgs->SG_AT.Cancel();
			//	  		sgs->SG_AT.SetDelay(Time(Seconds(180)));
			//	  		///sgs->SG_AT.SetFunction (&MulticastRoutingProtocol::???, this);
			//	  		sgs->SG_PLT.Cancel();
			//	  		sgs->SG_PLT.SetDelay(Seconds(210));
			//	  		///sgs->SG_PLT.SetFunction (&MulticastRoutingProtocol::???, this);
			//	  		sgs->SG_SAT.Cancel();
			//	  		sgs->SG_SAT.SetDelay(Seconds(210));
			//	  		///sgs->SG_SAT.SetFunction (&MulticastRoutingProtocol::???, this);
			//	  		sgs->SG_SRT.Cancel();
			//	  		sgs->SG_SRT.SetDelay(Seconds(60));
			//	  		///sgs->SG_SRT.SetFunction (&MulticastRoutingProtocol::???, this);
		}
	}

	void EraseSourceGroupState(uint32_t interface, const SourceGroupState &ns) {
		SourceGroupList *sgl = FindSourceGroupList(interface);
		if (!sgl)
			return;
		for (SourceGroupList::iterator iter = sgl->begin(); iter != sgl->end(); iter++) {
			if (*iter == ns) {
				sgl->erase(iter++);
			}
		}
	}

	void ChangeSourceGroupState(uint32_t oldinterface, uint32_t newinterface, const SourceGroupState &ns) {
		SourceGroupList *sgl = FindSourceGroupList(oldinterface);
		SourceGroupList *sgl_new = FindSourceGroupList(newinterface);
		if (!sgl || !sgl_new)
			return;
		for (SourceGroupList::iterator iter = sgl->begin(); iter != sgl->end(); iter++) {
			if (*iter == ns) {
				sgl_new->push_back(*iter);
				sgl->erase(iter++);
			}
		}
	}

	NeighborhoodStatus* FindNeighborhoodStatus(uint32_t interface) {
		std::map<uint32_t, NeighborhoodStatus>::iterator iter =
				m_IfaceNeighbors.find(interface);
		return (iter == m_IfaceNeighbors.end() ? NULL : &iter->second);
	}

	void InsertNeighborhoodStatus(const uint32_t interface) {
		if (!FindNeighborhoodStatus(interface)) {
			NeighborhoodStatus is;
			m_IfaceNeighbors.insert(std::pair<uint32_t, NeighborhoodStatus>(interface, is));
		}
	}

	void EraseNeighborhoodStatus(const uint32_t interface) {
		m_IfaceNeighbors.erase(interface);
	}

	NeighborState* FindNeighborState(uint32_t interface,const NeighborState &ns) {
		NeighborhoodStatus *status = FindNeighborhoodStatus(interface);
		if (!status)
			return NULL;
		NeighborList *list = &status->neighbors;
		for (NeighborList::iterator iter = list->begin(); iter != list->end(); iter++) {
			if (*iter == ns)
				return &(*iter);
		}
		return NULL;
	}

	void InsertNeighborState(uint32_t interface, const NeighborState &ns);

	void EraseNeighborState(uint32_t interface, const NeighborState &ns) {
		FindNeighborhoodStatus(interface)->neighbors.remove(ns);
	}

	void EraseNeighborState(const uint32_t interface) {
		std::map<uint32_t, NeighborhoodStatus>::iterator iter =
				m_IfaceNeighbors.find(interface);
		if (iter != m_IfaceNeighbors.end())
			m_IfaceNeighbors.erase(iter);
	}

//	void SetHelloTimerDelay(Time delay) {
//		hello_timer.SetDelay(delay);
//	}

	void SetStateRefreshCapable(uint32_t interface, bool state) {
		NeighborhoodStatus *in = FindNeighborhoodStatus(interface);
		in->stateRefreshCapable = state;
	}

	void SetLANDelayEnabled(uint32_t interface, bool state) {
		NeighborhoodStatus *in = FindNeighborhoodStatus(interface);
		in->LANDelayEnabled = state;
	}

	void SetPropagationDelay(uint32_t interface, Time delay) {
		NeighborhoodStatus *in = FindNeighborhoodStatus(interface);
		in->propagationDelay = delay;
	}

	void SetOverrideInterval(uint32_t interface, Time interval) {
		NeighborhoodStatus *in = FindNeighborhoodStatus(interface);
		in->overrideInterval = interval;
	}

	///
	/// \brief The most important macros are those defining the outgoing
	///   interface list (or "olist") for the relevant state.
	///   immediate_olist(S,G) = pim_nbrs (-) prunes(S,G) (+) ( pim_include(*,G) (-) pim_exclude(S,G) ) (+)
	///                           pim_include(S,G) (-) lost_assert(S,G) (-) boundary(G)
	/// \param source Source IPv4 address
	/// \param group Multicast group IPv4 address
	///
	std::set<uint32_t> immediate_olist(Ipv4Address source, Ipv4Address group) {

		std::vector<uint32_t> resA;
		std::set<uint32_t> pim_nbrz = pim_nbrs();/// The set pim_nbrs is the set of all interfaces on which the router has at least one active PIM neighbor.
		std::set<uint32_t> prunez = prunes(source, group); /// prunes(S,G) = {all interfaces I such that DownstreamPState(S,G,I) is in Pruned state}
		/// pim_nbrs *(-)* prunes(S,G)
		set_difference(pim_nbrz.begin(), pim_nbrz.end(), prunez.begin(),prunez.end(), resA.begin());

		std::vector<uint32_t> resB;
		std::set<uint32_t> inc = pim_include(NULL, group); /// pim_include(*,G) = {all interfaces I such that: local_receiver_include(*,G,I)}
		std::set<uint32_t> exc = pim_exclude(source, group); /// pim_exclude(S,G) = {all interfaces I such that: local_receiver_exclude(S,G,I)}
		/// pim_include(*,G) *(-)* pim_exclude(S,G)
		set_difference(inc.begin(), inc.end(), exc.begin(), exc.end(),resB.begin());

		std::vector<uint32_t> result;
		/// pim_nbrs (-) prunes(S,G) *(+)* (pim_include(*,G) (-) pim_exclude(S,G) )
		set_union(resA.begin(), resA.end(), resB.begin(), resB.end(),result.begin());

		std::set<uint32_t> incC = pim_include(source, group); /// pim_include(S,G) = {all interfaces I such that: local_receiver_include(S,G,I)}
		/// pim_nbrs (-) prunes(S,G) (+) (pim_include(*,G) (-) pim_exclude(S,G) ) *(+)* pim_include(S,G)
		set_union(result.begin(), result.end(), incC.begin(), incC.end(),resA.begin());

		std::set<uint32_t> lostC = lost_assert(source, group);
		/// pim_nbrs (-) prunes(S,G) (+) (pim_include(*,G) (-) pim_exclude(S,G) ) (+) pim_include(S,G) *(-)* lost_assert(S,G)
		set_difference(resA.begin(), resA.end(), lostC.begin(), lostC.end(),resB.begin());

		std::set<uint32_t> boundC = boundary(group);
		std::vector<uint32_t> resC;
		/// pim_nbrs (-) prunes(S,G) (+) (pim_include(*,G) (-) pim_exclude(S,G) ) (+) pim_include(S,G) (-) lost_assert(S,G) *(-)* boundary(G)
		set_difference(resB.begin(), resB.end(), boundC.begin(), boundC.end(),resC.begin());

		std::set<uint32_t> olist(resC.begin(), resC.end());

		return olist;
	}

	void SourceDirectlyConnected(SourceGroupPair &sgp);
	void SourceNoDirectlyConnected(SourceGroupPair &sgp);
	/// Basically RPF' is the RPF neighbor toward a source
	/// unless a PIM-DM Assert has overridden the normal choice of neighbor.

	void RPF_primeChanges(SourceGroupPair &sgp);

	void RPF_Changes(SourceGroupPair &sgp, uint32_t oldInterface, uint32_t newInterface);

	void olistCheck(SourceGroupPair &sgp, std::set<uint32_t> list);
	void olistEmpty(SourceGroupPair &sgp, std::set<uint32_t> list);
	void olistFull(SourceGroupPair &sgp, std::set<uint32_t> list);

	/// \brief The outgoing interfaces except the RPF_interface.
	///
	/// \param source Source IPv4 address
	/// \param group Multicast group IPv4 address
	std::set<uint32_t> olist(Ipv4Address source, Ipv4Address group) {
		std::set<uint32_t> _olist = immediate_olist(source, group);
		_olist.erase(RPF_interface(source));
		return _olist;
	}

	uint32_t UpstreamInterface(Ipv4Address source) {
		return RPF_interface(source);
	}

	std::set<uint32_t> DowntreamInterface(Ipv4Address source) {
		uint32_t upstream = UpstreamInterface(source);
		std::set<uint32_t> down;
		for (uint32_t i = 0; i < m_ipv4->GetNInterfaces(); i++) {
			if (i != upstream) {
				down.insert(i);
			}
		}
		return down;
	}

	/// \brief RPF interface towards the source S as indicated by the MRIB.
	/// \param source Source IPv4 address
	uint32_t RPF_interface(Ipv4Address source) {
		if (m_mrib.find(source) == m_mrib.end())
			return -1;
		return m_mrib.find(source)->second.interface;
	}

	/*
	 * The macro local_receiver_include(S,G,I) is true if the IGMP module or
	 * other local membership mechanism has determined that there are local
	 * members on interface I that seek to receive traffic sent specifically by S to G.
	 */
	bool local_receiver_include(Ipv4Address source, Ipv4Address group, uint32_t interface) {
		if(group==NULL){//no group - no way to identify members
//			NS_LOG_ERROR("Error: Source: "<< source<<", Group is NULL "<< group);
			return false;
		}
		else if(source!=NULL & group!=NULL){
			SourceGroupPair sgp(source,group);
			return (FindSourceGroupState(interface,sgp)==NULL?false:FindSourceGroupState(interface,sgp)->members);
		}else{
			SourceGroupList *sgl = FindSourceGroupList(interface);
			if (!sgl)
				return false;
			bool members = false;
			for (SourceGroupList::iterator iter = sgl->begin(); iter != sgl->end() && !members; iter++) {
				members |= (iter->SGPair.groupMulticastAddr == group && iter->members);
			}
			return members;
			//TODO need some local membership indicator: workaround a flag in the SG-state.
		}
	}

	//
	///The interfaces to which traffic might be forwarded because
	//   of hosts that are local members on those interfaces.
	//
	//   pim_include(*,G) = {all interfaces I such that: local_receiver_include(*,G,I)}
	//   pim_include(S,G) = {all interfaces I such that: local_receiver_include(S,G,I)}
	std::set<uint32_t> pim_include(Ipv4Address source, Ipv4Address group) {
		std::set<uint32_t> include;
		for (uint32_t i = 0; i < m_ipv4->GetNInterfaces(); i++) {
			if (local_receiver_include(source, group, i)) {
				include.insert(i);
			}
		}
		return include;
	}

	bool seek_traffic_from(Ipv4Address source, Ipv4Address group,uint32_t interface) {
		SourceGroupPair sgp(source,group);
		return (FindSourceGroupState(interface,sgp)==NULL?true:!(FindSourceGroupState(interface,sgp)->members));
	}

	// Local members for a (source,group) pair.
	// True if local_receiver_include(*,G,I) is true
	// but none of the local members seek to receive traffic from S.
	bool local_receiver_exclude(Ipv4Address source, Ipv4Address group, uint32_t interface) {
		return local_receiver_include(NULL, group, interface)
				&& seek_traffic_from(source,group,interface); // TODO
	}

	/// The interfaces to which traffic might not be forwarded because of hosts that are not local members on those interfaces.
	///   pim_exclude(S,G) = {all interfaces I such that: local_receiver_exclude(S,G,I)}
	std::set<uint32_t> pim_exclude(Ipv4Address source, Ipv4Address group) {
		std::set<uint32_t> exclude;
		for (uint32_t i = 0; i < m_ipv4->GetNInterfaces(); i++) {
			if (local_receiver_exclude(source, group, i)) {
				exclude.insert(i);
			}
		}
		return exclude;
	}

	/*
	 * All interfaces on which the router has at least one active PIM neighbor.
	 */
	std::set<uint32_t> pim_nbrs(void) {
		std::set<uint32_t> pimNbrs;
		for (uint32_t i = 0; i < m_ipv4->GetNInterfaces(); i++) {
			if (m_IfaceNeighbors.find(i)->second.neighbors.size() > 0) {
				pimNbrs.insert(i);
			}
		}
		return pimNbrs;
	}

	/*
	 * The set of all interfaces on which the router has received Prune(S,G) messages:
	 *      prunes(S,G) = {all interfaces I such that DownstreamPState(S,G,I) is in Pruned state}
	 */
	std::set<uint32_t> prunes(Ipv4Address source, Ipv4Address group) {
		std::set<uint32_t> prune;
		SourceGroupPair sgp(source,group);
		for (uint32_t i = 0; i < m_ipv4->GetNInterfaces(); i++) {
			SourceGroupState *sgState = FindSourceGroupState(i, sgp);
			if(!sgState) continue;
			if (i!=RPF_interface(source) && sgState->SGPruneState == Prune_Pruned) {
				prune.insert(i);
			}
		}
		return prune;
	}

	/*  The set lost_assert(S,G) is the set of all interfaces on which the
	 *    router has lost an (S,G) Assert.
	 *    lost_assert(S,G) = {all interfaces I such that
	 *                        lost_assert(S,G,I) == TRUE}
	 *
	 */
	std::set<uint32_t> lost_assert(Ipv4Address source, Ipv4Address group) {
		std::set<uint32_t> set;
		for (uint32_t i = 0; i < m_ipv4->GetNInterfaces(); i++) {
			if (lost_assert(source, group, i))
				set.insert(i);
		}
		return set;
	}

	/*
	 * True if the node has lost an (S,G) Assert on that interface.
	 */
	bool lost_assert(Ipv4Address source, Ipv4Address group, uint32_t interface) {
		if (RPF_interface(source) == interface) {
			return false;
		} else {
			return (AssertWinner(source, group, interface) != GetLocalAddress(interface)
					&& (AssertWinnerMetric(source, group, interface)
							> spt_assert_metric(source, interface)));
		}
	}

	bool boundary(uint32_t interface, Ipv4Address group){
		//TODO administratively scoped boundary
		return true;
	}

	/*
	 * boundary(G) = {all interfaces I with an administratively scoped boundary for group G}
	 */
	std::set<uint32_t> boundary(Ipv4Address G) {
		std::set<uint32_t> bound;
		for (uint32_t i = 0; i < m_ipv4->GetNInterfaces(); i++) {
			if(boundary(i,G)) //TODO administratively scoped boundary
			bound.insert(i);
		}
		return bound;
	}

	//The macro I_Am_Assert_loser(S, G, I) is true if the Assert state
	//   machine (in Section 4.6) for (S,G) on interface I is in the "I am
	//   Assert Loser" state.
	Ipv4Address RPF_prime(Ipv4Address source,Ipv4Address group) {
		if (I_Am_Assert_loser(source, group, RPF_interface(source))) {
			return AssertWinner(source, group, RPF_interface(source));
		} else {
			return m_mrib.find(source)->second.nextAddr;
		}
	}

	bool I_Am_Assert_loser(Ipv4Address source, Ipv4Address group, uint32_t interface) {
		SourceGroupState *sgState = FindSourceGroupState(RPF_interface(source),source,group);
		return sgState->SGAssertState == Assert_Loser;
	}
	//TODO and AssertWinnerMetric(S,G,I) defaults to Infinity when in the NoInfo state.
	struct AssertMetric AssertWinnerMetric(Ipv4Address source, Ipv4Address group, uint32_t interface) {
		struct AssertMetric assertMetric(0, 0,source.Get());
		return assertMetric;
	}

	struct AssertMetric spt_assert_metric(Ipv4Address source, //Ipv4Address group,
			uint32_t interface) {
		struct AssertMetric assertMetric;
		assertMetric.metric_preference = m_mrib.find(source)->second.metricPreference;
		assertMetric.route_metric = m_mrib.find(source)->second.route_metric;
		assertMetric.ip_address = GetLocalAddress(interface); //TODO local node address on that interface?
		return assertMetric;
	}
	struct AssertMetric infinite_assert_metric(){
		struct AssertMetric assertMetric;
		assertMetric.metric_preference= 0xFFFFFFFF;
		assertMetric.route_metric = 0xFFFFFFFF;
		assertMetric.ip_address = Ipv4Address("255.255.255.255");
		return assertMetric;
	}

	bool CouldAssert (Ipv4Address source, Ipv4Address group, uint32_t interface) {
		return RPF_interface(source) != interface;
	}

	struct AssertMetric my_assert_metric (Ipv4Address source, Ipv4Address group, uint32_t interface) {
		if (CouldAssert(source,group,interface)) {
			return spt_assert_metric(source, interface);
		} else {
			return infinite_assert_metric();
		}
	}

	//TODO AssertWinner(S,G,I) defaults to NULL,
	Ipv4Address AssertWinner(Ipv4Address source, Ipv4Address group,uint32_t interface) {
		SourceGroupState *sgState = FindSourceGroupState(interface, source, group);
		if(!sgState)
			return NULL;
		return sgState->SGAW;
	}

	//StateRefreshRateLimit(S,G) is TRUE if the time elapsed since the last received StateRefresh(S,G)
	//	is less than the configured RefreshLimitInterval.
	bool StateRefreshRateLimit(Ipv4Address source, Ipv4Address group){
		return FindSourceGroupState(RPF_interface(source),source,group)->lastStateRefresh.GetSeconds() < RefreshInterval;
	}

	bool StateRefreshCapable(uint32_t interface){
		return FindNeighborhoodStatus(interface)->stateRefreshCapable;
	}

};

}
}// namespace pimdm, ns3
#endif
