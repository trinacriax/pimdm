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

#ifndef PIM_DM_HELPER_H
#define PIM_DM_HELPER_H

#include <ns3/object-factory.h>
#include <ns3/node.h>
#include <ns3/node-container.h>
#include <ns3/ipv4-routing-helper.h>
#include <map>
#include <set>

namespace ns3
{

  /**
   * \brief Helper class that adds pimdm routing to nodes.
   *
   * This class is expected to be used in conjunction with
   * ns3::InternetStackHelper::SetRoutingHelper
   */
  class PimDmHelper : public Ipv4RoutingHelper
  {
    public:
      /**
       * Create an pimdmHelper that makes life easier for people who want to install
       * pimdm routing to nodes.
       */
      PimDmHelper ();

      /**
       * \brief Construct an pimdmHelper from another previously initialized instance
       * (Copy Constructor).
       */
      PimDmHelper (const PimDmHelper &);

      /**
       * \internal
       * \returns pointer to clone of this pimdmHelper
       *
       * This method is mainly for internal use by the other helpers;
       * clients are expected to free the dynamic memory allocated by this method
       */
      PimDmHelper*
      Copy (void) const;

      /**
       * \param node the node for which an exception is to be defined
       * \param interface an interface of node on which pimdm is not to be installed
       *
       * This method allows the user to specify an interface on which pimdm is not to be installed on
       */
      void
      ExcludeInterface (Ptr<Node> node, uint32_t interface);

      /**
       * \param node the node on which the routing protocol will run
       * \returns a newly-created routing protocol
       *
       * This method will be called by ns3::InternetStackHelper::Install
       */
      virtual Ptr<Ipv4RoutingProtocol>
      Create (Ptr<Node> node) const;

      /**
       * \param name the name of the attribute to set
       * \param value the value of the attribute to set.
       *
       * This method controls the attributes of ns3::pimdm::RoutingProtocol
       */
      void
      Set (std::string name, const AttributeValue &value);

    private:
      /**
       * \internal
       * \brief Assignment operator declared private and not implemented to disallow
       * assignment and prevent the compiler from happily inserting its own.
       */
      PimDmHelper &
      operator = (const PimDmHelper &o);
      ObjectFactory m_agentFactory;

      std::map<Ptr<Node>, std::set<uint32_t> > m_interfaceExclusions;
  };

} // namespace ns3

#endif /* PIM_DM_HELPER_H */
