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
 * Source:  http://www.ietf.org/rfc/rfc3973.txt
 *
 * Authors: Alessandro Russo <russo@disi.unitn.it>
 *          University of Trento, Italy
 *          University of California, Los Angeles U.S.A.
 */

#include "ns3/test.h"
#include "ns3/pimdm-packet.h"
#include "ns3/packet.h"

namespace ns3 {

class PimDmHelloTestCase : public TestCase {
public:
  PimDmHelloTestCase ();
  virtual void DoRun (void);
};

PimDmHelloTestCase::PimDmHelloTestCase ()
  : TestCase ("Check Hello PIM-DM messages")
{}
void
PimDmHelloTestCase::DoRun (void)
{
  Packet packet;
  pimdm::PIMHeader msgIn;
  msgIn.SetVersion(2);
  msgIn.SetType(pimdm::PIM_HELLO);
  msgIn.SetReserved(0);
  pimdm::PIMHeader::HelloMessage &helloMessage = msgIn.GetHelloMessage();
  {
	pimdm::PIMHeader::HelloMessage::HelloEntry helloIn1;
	helloIn1.m_optionType = pimdm::PIMHeader::HelloMessage::HelloHoldTime;
	helloIn1.m_optionLength = PIM_DM_HELLO_HOLDTIME;
	struct pimdm::PIMHeader::HelloMessage::HelloEntry::HoldTime tmp1 = {Time("1401s")};
	helloIn1.m_optionValue.holdTime = tmp1;
	helloMessage.m_optionList.push_back(helloIn1);

	pimdm::PIMHeader::HelloMessage::HelloEntry helloIn2;
	helloIn2.m_optionType = pimdm::PIMHeader::HelloMessage::LANPruneDelay;
	helloIn2.m_optionLength = PIM_DM_HELLO_LANPRUNDELAY;
	struct pimdm::PIMHeader::HelloMessage::HelloEntry::LanPruneDelay tmp2 = {1,Time("10ms"),Time("20ms")};
	helloIn2.m_optionValue.lanPruneDelay = tmp2;
	helloMessage.m_optionList.push_back(helloIn2);

	pimdm::PIMHeader::HelloMessage::HelloEntry helloIn3;
	helloIn3.m_optionType = pimdm::PIMHeader::HelloMessage::HelloHoldTime;
	helloIn3.m_optionLength = PIM_DM_HELLO_HOLDTIME;
	struct pimdm::PIMHeader::HelloMessage::HelloEntry::HoldTime tmp3 = {Time("2802s")};
	helloIn3.m_optionValue.holdTime = tmp3;
	helloMessage.m_optionList.push_back(helloIn3);

	pimdm::PIMHeader::HelloMessage::HelloEntry helloIn4;
	helloIn4.m_optionType = pimdm::PIMHeader::HelloMessage::GenerationID;
	helloIn4.m_optionLength = PIM_DM_HELLO_GENERATIONID;
	struct pimdm::PIMHeader::HelloMessage::HelloEntry::GenerationID tmp4 = {1234567890};
	helloIn4.m_optionValue.generationID = tmp4;
	helloMessage.m_optionList.push_back(helloIn4);

	pimdm::PIMHeader::HelloMessage::HelloEntry helloIn5;
	helloIn5.m_optionType = pimdm::PIMHeader::HelloMessage::StateRefreshCapable;
	helloIn5.m_optionLength = PIM_DM_HELLO_STATEREFRESH;
	struct pimdm::PIMHeader::HelloMessage::HelloEntry::StateRefreshCapable tmp5 = {9,18,9999};
	helloIn5.m_optionValue.stateRefreshCapable = tmp5;
	helloMessage.m_optionList.push_back(helloIn5);

    packet.AddHeader(msgIn);
  }
  {
  pimdm::PIMHeader msgOut;
  packet.RemoveHeader (msgOut);
  msgOut.Print(std::cout);
  pimdm::PIMHeader::HelloMessage &helloOut = msgOut.GetHelloMessage();

	NS_TEST_ASSERT_MSG_EQ(msgOut.GetVersion(),2,"PIM Version");
	NS_TEST_ASSERT_MSG_EQ(msgOut.GetReserved(),0,"Reserved");
	NS_TEST_ASSERT_MSG_EQ(msgOut.GetType(),pimdm::PIM_HELLO,"PIM Type");

	pimdm::PIMHeader::HelloMessage::HelloEntry helloEntry1 = helloOut.m_optionList[0];
//	helloEntry1
	NS_TEST_ASSERT_MSG_EQ (helloEntry1.m_optionType, pimdm::PIMHeader::HelloMessage::HelloHoldTime, "Option Type");
	NS_TEST_ASSERT_MSG_EQ (helloEntry1.m_optionLength, PIM_DM_HELLO_HOLDTIME, "Option Length");
	NS_TEST_ASSERT_MSG_EQ (helloEntry1.m_optionValue.holdTime.m_holdTime,Time("1401s"),"Option Value");

	pimdm::PIMHeader::HelloMessage::HelloEntry helloEntry2 = helloOut.m_optionList[1];

	NS_TEST_ASSERT_MSG_EQ (helloEntry2.m_optionType, pimdm::PIMHeader::HelloMessage::LANPruneDelay, "Option Type");
	NS_TEST_ASSERT_MSG_EQ (helloEntry2.m_optionLength, PIM_DM_HELLO_LANPRUNDELAY, "Option Length");
	NS_TEST_ASSERT_MSG_EQ (helloEntry2.m_optionValue.lanPruneDelay.m_T,1, "Option Value");
	NS_TEST_ASSERT_MSG_EQ (helloEntry2.m_optionValue.lanPruneDelay.m_propagationDelay,Time("10ms"), "Option Value");
	NS_TEST_ASSERT_MSG_EQ (helloEntry2.m_optionValue.lanPruneDelay.m_overrideInterval,Time("20ms"), "Option Value");

	pimdm::PIMHeader::HelloMessage::HelloEntry helloEntry3 = helloOut.m_optionList[2];
	std::cout <<"\n\tType "<<helloEntry3.m_optionType << " Length "<< helloEntry3.m_optionLength
			<< " Value ["<<helloEntry3.m_optionValue.holdTime.m_holdTime<<"]\n";
	NS_TEST_ASSERT_MSG_EQ (helloEntry3.m_optionType, pimdm::PIMHeader::HelloMessage::HelloHoldTime, "Option Type");
	NS_TEST_ASSERT_MSG_EQ (helloEntry3.m_optionLength, PIM_DM_HELLO_HOLDTIME, "Option Length");
	NS_TEST_ASSERT_MSG_EQ (helloEntry3.m_optionValue.holdTime.m_holdTime,Time("2802s"), "Option Value");

	pimdm::PIMHeader::HelloMessage::HelloEntry helloEntry4 = helloOut.m_optionList[3];
	std::cout <<"\n\tType "<<helloEntry4.m_optionType << " Length "<< helloEntry4.m_optionLength
			<< " Value ["<<helloEntry4.m_optionValue.generationID.m_generatioID<<"]\n";
	NS_TEST_ASSERT_MSG_EQ (helloEntry4.m_optionType, pimdm::PIMHeader::HelloMessage::GenerationID, "Option Type");
	NS_TEST_ASSERT_MSG_EQ (helloEntry4.m_optionLength, PIM_DM_HELLO_GENERATIONID, "Option Length");
	NS_TEST_ASSERT_MSG_EQ (helloEntry4.m_optionValue.generationID.m_generatioID,1234567890, "Option Value");

	pimdm::PIMHeader::HelloMessage::HelloEntry helloEntry5 = helloOut.m_optionList[4];
	std::cout <<"\n\tType "<<helloEntry5.m_optionType << " Length "<< helloEntry5.m_optionLength
		<< " Value ["<<(uint16_t)helloEntry5.m_optionValue.stateRefreshCapable.m_version<<","
		<< (uint16_t)helloEntry5.m_optionValue.stateRefreshCapable.m_interval <<","
		<< helloEntry5.m_optionValue.stateRefreshCapable.m_reserved<<"]\n";
	NS_TEST_ASSERT_MSG_EQ (helloEntry5.m_optionType, pimdm::PIMHeader::HelloMessage::StateRefreshCapable, "Option Type");
	NS_TEST_ASSERT_MSG_EQ (helloEntry5.m_optionLength, PIM_DM_HELLO_STATEREFRESH, "Option Length");
	NS_TEST_ASSERT_MSG_EQ (helloEntry5.m_optionValue.stateRefreshCapable.m_version,9, "Option Value");
	NS_TEST_ASSERT_MSG_EQ (helloEntry5.m_optionValue.stateRefreshCapable.m_interval,18, "Option Value");
	NS_TEST_ASSERT_MSG_EQ (helloEntry5.m_optionValue.stateRefreshCapable.m_reserved,9999, "Option Value");
  }
}


class PimDmJoinPruneTestCase : public TestCase {
public:
	PimDmJoinPruneTestCase ();
  virtual void DoRun (void);
};

PimDmJoinPruneTestCase::PimDmJoinPruneTestCase ()
  : TestCase ("Check Join-Prune PIM-DM messages")
{}
void
PimDmJoinPruneTestCase::DoRun (void)
{
  Packet packet;
  pimdm::PIMHeader msgIn;
  msgIn.SetVersion(2);
  msgIn.SetType(pimdm::PIM_JP);
  msgIn.SetReserved(0);
  pimdm::PIMHeader::JoinPruneMessage &messageIn = msgIn.GetJoinPruneMessage();
  {
	pimdm::PIMHeader::EncodedUnicast eu = {5,10,Ipv4Address("192.168.1.1")};
	messageIn.m_joinPruneMessage.m_upstreamNeighborAddr = eu;
	messageIn.m_joinPruneMessage.m_reserved = 0;
	messageIn.m_joinPruneMessage.m_numGroups = 2;
	messageIn.m_joinPruneMessage.m_holdTime = Time("1401s");
	pimdm::PIMHeader::MulticastGroupEntry m_entry1;
	{
		pimdm::PIMHeader::EncodedGroup eg = {(uint8_t)7,(uint8_t)14,(uint8_t)0,(uint8_t)0,(uint8_t)1,(uint8_t)4,Ipv4Address("192.168.10.10")};
		m_entry1.m_multicastGroupAddr = eg;
		m_entry1.m_numberJoinedSources = 2;
		m_entry1.m_numberPrunedSources = 2;
		{
			pimdm::PIMHeader::EncodedSource j1 = {8,16,0,1,0,0,4,Ipv4Address("192.168.10.20")};
			m_entry1.m_joinedSourceAddrs.push_back(j1);
			pimdm::PIMHeader::EncodedSource j2 = {9,18,0,0,1,0,6,Ipv4Address("192.168.10.22")};
			m_entry1.m_joinedSourceAddrs.push_back(j2);
		}
		{
			pimdm::PIMHeader::EncodedSource p1 = {3,6,0,1,0,0,8,Ipv4Address("192.168.10.40")};
			m_entry1.m_prunedSourceAddrs.push_back(p1);
			pimdm::PIMHeader::EncodedSource p2 = {4,8,0,0,1,0,7,Ipv4Address("192.168.10.42")};
			m_entry1.m_prunedSourceAddrs.push_back(p2);
		}
	}
	messageIn.m_multicastGroups.push_back(m_entry1);
	pimdm::PIMHeader::MulticastGroupEntry m_entry2;
		{
			pimdm::PIMHeader::EncodedGroup eg = {0,1,1,0,1,1,Ipv4Address("192.168.10.8")};
			m_entry2.m_multicastGroupAddr = eg;
			m_entry2.m_numberJoinedSources = 1;
			m_entry2.m_numberPrunedSources = 1;
			{
				pimdm::PIMHeader::EncodedSource j1 = {1,2,0,0,0,0,4,Ipv4Address("192.168.10.70")};
				m_entry2.m_joinedSourceAddrs.push_back(j1);
			}
			{
				pimdm::PIMHeader::EncodedSource p1 = {2,4,0,1,0,0,8,Ipv4Address("192.168.10.72")};
				m_entry2.m_prunedSourceAddrs.push_back(p1);
			}
		}
	messageIn.m_multicastGroups.push_back(m_entry2);
    packet.AddHeader(msgIn);
  }
  {
  pimdm::PIMHeader msgOut;
  packet.RemoveHeader (msgOut);
  msgOut.Print(std::cout);

  NS_TEST_ASSERT_MSG_EQ(msgOut.GetVersion(),2,"PIM Version");
  NS_TEST_ASSERT_MSG_EQ(msgOut.GetReserved(),0,"Reserved");
  NS_TEST_ASSERT_MSG_EQ(msgOut.GetType(),pimdm::PIM_JP,"PIM Type");
	pimdm::PIMHeader::JoinPruneMessage &message = msgOut.GetJoinPruneMessage();
	pimdm::PIMHeader::JoinPruneGraftMessage jpg = message.m_joinPruneMessage;
	jpg.Print(std::cout);
	{
		NS_TEST_ASSERT_MSG_EQ (jpg.m_upstreamNeighborAddr.m_addressFamily,5, "Address Family");
		NS_TEST_ASSERT_MSG_EQ (jpg.m_upstreamNeighborAddr.m_encodingType,10, "Encoding");
		NS_TEST_ASSERT_MSG_EQ (jpg.m_upstreamNeighborAddr.m_unicastAddress,Ipv4Address("192.168.1.1"), "Unicast Address");
	}
	NS_TEST_ASSERT_MSG_EQ (jpg.m_reserved,0, "Reserved");
	NS_TEST_ASSERT_MSG_EQ (jpg.m_numGroups, 2,"Groups");
	NS_TEST_ASSERT_MSG_EQ (jpg.m_holdTime , Time("1401s") , "Hold Time");

	pimdm::PIMHeader::MulticastGroupEntry mge1 = message.m_multicastGroups[0];
	mge1.Print(std::cout);
	pimdm::PIMHeader::EncodedGroup gp1 = mge1.m_multicastGroupAddr;
	NS_TEST_ASSERT_MSG_EQ (gp1.m_addressFamily, 7, "Address Family");
	NS_TEST_ASSERT_MSG_EQ (gp1.m_encodingType, 14, "Encoding");
	NS_TEST_ASSERT_MSG_EQ (gp1.m_B, 0, "B");
	NS_TEST_ASSERT_MSG_EQ (gp1.m_reserved, 0, "Reserved");
	NS_TEST_ASSERT_MSG_EQ (gp1.m_Z, 1, "Z");
	NS_TEST_ASSERT_MSG_EQ (gp1.m_maskLength, 4, "Mask Length");
	NS_TEST_ASSERT_MSG_EQ (gp1.m_groupAddress, Ipv4Address("192.168.10.10"), "Encoding");
	NS_TEST_ASSERT_MSG_EQ (mge1.m_numberJoinedSources,2,"Joined Sources");
	NS_TEST_ASSERT_MSG_EQ (mge1.m_numberPrunedSources,2,"Joined Sources");

	pimdm::PIMHeader::EncodedSource es1 = mge1.m_joinedSourceAddrs[0];
	NS_TEST_ASSERT_MSG_EQ (es1.m_addressFamily ,8,"Address Family");
	NS_TEST_ASSERT_MSG_EQ (es1.m_encodingType,16,"Encoding");
	NS_TEST_ASSERT_MSG_EQ (es1.m_reserved,0,"Reserved");
	NS_TEST_ASSERT_MSG_EQ (es1.m_S,1,"S");
	NS_TEST_ASSERT_MSG_EQ (es1.m_W,0,"W");
	NS_TEST_ASSERT_MSG_EQ (es1.m_R,0,"R");
	NS_TEST_ASSERT_MSG_EQ (es1.m_maskLength,4,"Mask Length");
	NS_TEST_ASSERT_MSG_EQ (es1.m_sourceAddress,Ipv4Address("192.168.10.20"),"Mask Length");

	pimdm::PIMHeader::EncodedSource es2 = mge1.m_joinedSourceAddrs[1];
	NS_TEST_ASSERT_MSG_EQ (es2.m_addressFamily ,9,"Address Family");
	NS_TEST_ASSERT_MSG_EQ (es2.m_encodingType,18,"Encoding");
	NS_TEST_ASSERT_MSG_EQ (es2.m_reserved,0,"Reserved");
	NS_TEST_ASSERT_MSG_EQ (es2.m_S,0,"S");
	NS_TEST_ASSERT_MSG_EQ (es2.m_W,1,"W");
	NS_TEST_ASSERT_MSG_EQ (es2.m_R,0,"R");
	NS_TEST_ASSERT_MSG_EQ (es2.m_maskLength,6,"Mask Length");
	NS_TEST_ASSERT_MSG_EQ (es2.m_sourceAddress,Ipv4Address("192.168.10.22"),"Mask Length");

	pimdm::PIMHeader::EncodedSource pn1 = mge1.m_prunedSourceAddrs[0];
	NS_TEST_ASSERT_MSG_EQ (pn1.m_addressFamily ,3,"Address Family");
	NS_TEST_ASSERT_MSG_EQ (pn1.m_encodingType,6,"Encoding");
	NS_TEST_ASSERT_MSG_EQ (pn1.m_reserved,0,"Reserved");
	NS_TEST_ASSERT_MSG_EQ (pn1.m_S,1,"S");
	NS_TEST_ASSERT_MSG_EQ (pn1.m_W,0,"W");
	NS_TEST_ASSERT_MSG_EQ (pn1.m_R,0,"R");
	NS_TEST_ASSERT_MSG_EQ (pn1.m_maskLength,8,"Mask Length");
	NS_TEST_ASSERT_MSG_EQ (pn1.m_sourceAddress,Ipv4Address("192.168.10.40"),"Mask Length");

	pimdm::PIMHeader::EncodedSource pn2 = mge1.m_prunedSourceAddrs[1];
	NS_TEST_ASSERT_MSG_EQ (pn2.m_addressFamily ,4,"Address Family");
	NS_TEST_ASSERT_MSG_EQ (pn2.m_encodingType,8,"Encoding");
	NS_TEST_ASSERT_MSG_EQ (pn2.m_reserved,0,"Reserved");
	NS_TEST_ASSERT_MSG_EQ (pn2.m_S,0,"S");
	NS_TEST_ASSERT_MSG_EQ (pn2.m_W,1,"W");
	NS_TEST_ASSERT_MSG_EQ (pn2.m_R,0,"R");
	NS_TEST_ASSERT_MSG_EQ (pn2.m_maskLength,7,"Mask Length");
	NS_TEST_ASSERT_MSG_EQ (pn2.m_sourceAddress,Ipv4Address("192.168.10.42"),"Mask Length");


	pimdm::PIMHeader::MulticastGroupEntry mge2 = message.m_multicastGroups[1];
	mge2.Print(std::cout);
	pimdm::PIMHeader::EncodedGroup gp2 = mge2.m_multicastGroupAddr;
	NS_TEST_ASSERT_MSG_EQ (gp2.m_addressFamily, 0, "Address Family");
	NS_TEST_ASSERT_MSG_EQ (gp2.m_encodingType, 1, "Encoding");
	NS_TEST_ASSERT_MSG_EQ (gp2.m_B, 1, "B");
	NS_TEST_ASSERT_MSG_EQ (gp2.m_reserved, 0, "Reserved");
	NS_TEST_ASSERT_MSG_EQ (gp2.m_Z, 1, "Z");
	NS_TEST_ASSERT_MSG_EQ (gp2.m_maskLength, 1, "Mask Length");
	NS_TEST_ASSERT_MSG_EQ (gp2.m_groupAddress, Ipv4Address("192.168.10.8"), "Encoding");
	NS_TEST_ASSERT_MSG_EQ (mge2.m_numberJoinedSources,1,"Joined Sources");
	NS_TEST_ASSERT_MSG_EQ (mge2.m_numberPrunedSources,1,"Joined Sources");

	pimdm::PIMHeader::EncodedSource es3 = mge2.m_joinedSourceAddrs[0];
	NS_TEST_ASSERT_MSG_EQ (es3.m_addressFamily ,1,"Address Family");
	NS_TEST_ASSERT_MSG_EQ (es3.m_encodingType,2,"Encoding");
	NS_TEST_ASSERT_MSG_EQ (es3.m_reserved,0,"Reserved");
	NS_TEST_ASSERT_MSG_EQ (es3.m_S,0,"S");
	NS_TEST_ASSERT_MSG_EQ (es3.m_W,0,"W");
	NS_TEST_ASSERT_MSG_EQ (es3.m_R,0,"R");
	NS_TEST_ASSERT_MSG_EQ (es3.m_maskLength,4,"Mask Length");
	NS_TEST_ASSERT_MSG_EQ (es3.m_sourceAddress,Ipv4Address("192.168.10.70"),"Mask Length");

	pimdm::PIMHeader::EncodedSource pn3 = mge2.m_prunedSourceAddrs[0];
	NS_TEST_ASSERT_MSG_EQ (pn3.m_addressFamily,2,"Address Family");
	NS_TEST_ASSERT_MSG_EQ (pn3.m_encodingType,4,"Encoding");
	NS_TEST_ASSERT_MSG_EQ (pn3.m_reserved,0,"Reserved");
	NS_TEST_ASSERT_MSG_EQ (pn3.m_S,1,"S");
	NS_TEST_ASSERT_MSG_EQ (pn3.m_W,0,"W");
	NS_TEST_ASSERT_MSG_EQ (pn3.m_R,0,"R");
	NS_TEST_ASSERT_MSG_EQ (pn3.m_maskLength,8,"Mask Length");
	NS_TEST_ASSERT_MSG_EQ (pn3.m_sourceAddress,Ipv4Address("192.168.10.72"),"Mask Length");
  }
}

class PimDmAssertTestCase : public TestCase {
public:
	PimDmAssertTestCase ();
  virtual void DoRun (void);
};

PimDmAssertTestCase::PimDmAssertTestCase ()
  : TestCase ("Check PIM-DM Assert messages")
{}
void
PimDmAssertTestCase::DoRun (void)
{
  Packet packet;
  pimdm::PIMHeader msgIn;
  msgIn.SetVersion(2);
  msgIn.SetType(pimdm::PIM_ASSERT);
  msgIn.SetReserved(0);
  pimdm::PIMHeader::AssertMessage &assertMessage = msgIn.GetAssertMessage();
  {
	pimdm::PIMHeader::EncodedGroup eg= {6,5,1,0,0,4,Ipv4Address("192.168.6.3")};
	assertMessage.m_multicastGroupAddr = eg;
	pimdm::PIMHeader::EncodedUnicast eu = {7,8,Ipv4Address("192.168.6.6")};
	assertMessage.m_sourceAddr = eu;
	assertMessage.m_R = 1;
	assertMessage.m_metricPreference = 0x0FFFFFFF;
	assertMessage.m_metric = 0xFFFFFFFF;
    packet.AddHeader(msgIn);
  }
  {
  pimdm::PIMHeader msgOut;
  packet.RemoveHeader (msgOut);
  msgOut.Print(std::cout);
  NS_TEST_ASSERT_MSG_EQ(msgOut.GetVersion(),2,"PIM Version");
  NS_TEST_ASSERT_MSG_EQ(msgOut.GetReserved(),0,"Reserved");
  NS_TEST_ASSERT_MSG_EQ(msgOut.GetType(),pimdm::PIM_ASSERT,"PIM Type");
  pimdm::PIMHeader::AssertMessage &assertOut = msgOut.GetAssertMessage();
  assertOut.Print(std::cout);
	NS_TEST_ASSERT_MSG_EQ(assertOut.m_multicastGroupAddr.m_addressFamily,6, "Address Family");
	NS_TEST_ASSERT_MSG_EQ(assertOut.m_multicastGroupAddr.m_encodingType,5, "Encoding type");
	NS_TEST_ASSERT_MSG_EQ(assertOut.m_multicastGroupAddr.m_B,1, "B");
	NS_TEST_ASSERT_MSG_EQ(assertOut.m_multicastGroupAddr.m_reserved,0, "Reserved");
	NS_TEST_ASSERT_MSG_EQ(assertOut.m_multicastGroupAddr.m_Z,0, "Z");
	NS_TEST_ASSERT_MSG_EQ(assertOut.m_multicastGroupAddr.m_maskLength,4, "Mask Length");
	NS_TEST_ASSERT_MSG_EQ(assertOut.m_multicastGroupAddr.m_groupAddress,Ipv4Address("192.168.6.3"), "Group Address");

	NS_TEST_ASSERT_MSG_EQ(assertOut.m_sourceAddr.m_addressFamily,7, "Address Family");
	NS_TEST_ASSERT_MSG_EQ(assertOut.m_sourceAddr.m_encodingType,8, "Encoding type");
	NS_TEST_ASSERT_MSG_EQ(assertOut.m_sourceAddr.m_unicastAddress,Ipv4Address("192.168.6.6"), "Unicast Address");

	NS_TEST_ASSERT_MSG_EQ(assertOut.m_R,1, "R");
	NS_TEST_ASSERT_MSG_EQ(assertOut.m_metricPreference,0x0FFFFFFF, "Metric Preference");
	NS_TEST_ASSERT_MSG_EQ(assertOut.m_metric,0xFFFFFFFF, "Metric");
  }
}


class PimDmStateRefreshTestCase : public TestCase {
public:
	PimDmStateRefreshTestCase ();
  virtual void DoRun (void);
};

PimDmStateRefreshTestCase::PimDmStateRefreshTestCase ()
  : TestCase ("Check PIM-DM State Refresh messages")
{}
void
PimDmStateRefreshTestCase::DoRun (void)
{
  Packet packet;
  pimdm::PIMHeader msgIn;
  msgIn.SetVersion(2);
  msgIn.SetType(pimdm::PIM_STATE_REF);
  msgIn.SetReserved(0);
  msgIn.SetChecksum(0);
  pimdm::PIMHeader::StateRefreshMessage &stateIn = msgIn.GetStateRefreshMessage();
  {
	pimdm::PIMHeader::EncodedGroup eg= {6,5,1,0,0,4,Ipv4Address("192.168.6.3")};
	stateIn.m_multicastGroupAddr = eg;
	pimdm::PIMHeader::EncodedUnicast eu = {7,8,Ipv4Address("192.168.6.6")};
	stateIn.m_sourceAddr = eu;
	pimdm::PIMHeader::EncodedUnicast ou = {20,98,Ipv4Address("192.169.2.6")};
	stateIn.m_originatorAddr = ou;
	stateIn.m_R = 1;
	stateIn.m_metricPreference = 0x0FFFFFFF;
	stateIn.m_metric = 0xFFFFFFFF;
	stateIn.m_maskLength = 4;
	stateIn.m_ttl = 7;
	stateIn.m_P = 1;
	stateIn.m_N = 0;
	stateIn.m_O = 1;
	stateIn.m_reserved = 0;
	stateIn.m_interval = 10;
	packet.AddHeader(msgIn);
  }
  {
  pimdm::PIMHeader msgOut;
  packet.RemoveHeader (msgOut);
  msgOut.Print(std::cout);
  NS_TEST_ASSERT_MSG_EQ(msgOut.GetVersion(),2,"PIM Version");
  NS_TEST_ASSERT_MSG_EQ(msgOut.GetReserved(),0,"Reserved");
  NS_TEST_ASSERT_MSG_EQ(msgOut.GetType(),pimdm::PIM_STATE_REF,"PIM Type");
  pimdm::PIMHeader::StateRefreshMessage &stateOut = msgOut.GetStateRefreshMessage();
  stateOut.Print(std::cout);
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_multicastGroupAddr.m_addressFamily,6, "Address Family");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_multicastGroupAddr.m_encodingType,5, "Encoding type");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_multicastGroupAddr.m_B,1, "B");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_multicastGroupAddr.m_reserved,0, "Reserved");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_multicastGroupAddr.m_Z,0, "Z");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_multicastGroupAddr.m_maskLength,4, "Mask Length");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_multicastGroupAddr.m_groupAddress,Ipv4Address("192.168.6.3"), "Group Address");

	NS_TEST_ASSERT_MSG_EQ(stateOut.m_sourceAddr.m_addressFamily,7, "Address Family");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_sourceAddr.m_encodingType,8, "Encoding type");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_sourceAddr.m_unicastAddress,Ipv4Address("192.168.6.6"), "Unicast Address");

	NS_TEST_ASSERT_MSG_EQ(stateOut.m_originatorAddr.m_addressFamily,20, "Address Family");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_originatorAddr.m_encodingType,98, "Encoding type");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_originatorAddr.m_unicastAddress,Ipv4Address("192.169.2.6"), "Unicast Address");

	NS_TEST_ASSERT_MSG_EQ(stateOut.m_R,1, "R");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_metricPreference,0x0FFFFFFF, "Metric Preference");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_metric,0xFFFFFFFF, "Metric");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_maskLength,4, "Mask Length");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_ttl,7, "TTL");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_P,1, "P");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_N,0, "N");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_O,1, "O");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_reserved,0, "Reserved");
	NS_TEST_ASSERT_MSG_EQ(stateOut.m_interval,10, "Interval");
  }
}

static class PimDmTestSuite : public TestSuite
{
public:
	PimDmTestSuite ();
} j_pimdmTestSuite;

PimDmTestSuite::PimDmTestSuite()
  : TestSuite("pimdm-header", UNIT)
{
  // RUN $ ./test.py -s pimdm-header -v -c unit 1
  AddTestCase(new PimDmHelloTestCase());
  AddTestCase(new PimDmJoinPruneTestCase());//graft and graftAck are identical in format to the Join/Prune Message
  AddTestCase(new PimDmAssertTestCase());
  AddTestCase(new PimDmStateRefreshTestCase());
}

} // namespace ns3

