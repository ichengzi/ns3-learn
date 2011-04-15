/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 TELEMATICS LAB, DEE - Politecnico di Bari
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
 * Author: Giuseppe Piro  <g.piro@poliba.it>
 * Author: Marco Miozzo <marco.miozzo@cttc.es> : Update to FF API Architecture
 */

#ifndef LTE_ENB_NET_DEVICE_H
#define LTE_ENB_NET_DEVICE_H

#include "lte-net-device.h"
#include "ns3/event-id.h"
#include "ns3/mac48-address.h"
#include "ns3/traced-callback.h"
#include "ns3/nstime.h"
#include "ns3/log.h"
#include "lte-phy.h"
#include <vector>

namespace ns3 {

class Packet;
class PacketBurst;
class Node;
class LtePhy;
class LteEnbPhy;
class LteEnbMac;
class LteEnbRrc;
class FfMacScheduler;


/**
 * The eNodeB device implementation
 */
class LteEnbNetDevice : public LteNetDevice
{
public:
  static TypeId GetTypeId (void);

  LteEnbNetDevice (void);
  /**
   * \brief Create eNB net device
   * \param node the network node
   * \param phy the physical object attached to it
   * \param mac the mac layer object attached to it
   * \param sched the scheduler object attached to it
   * \param rrc the rrc entity object attached to it
   */
  LteEnbNetDevice (Ptr<Node> node, Ptr<LteEnbPhy> phy, Ptr<LteEnbMac> mac, Ptr<FfMacScheduler> sched, Ptr<LteEnbRrc> rrc);

  virtual ~LteEnbNetDevice (void);
  virtual void DoDispose (void);

  /**
   * \return a pointer to the MAC 
   */
  Ptr<LteEnbMac> GetMac (void) const;

  /**
   * \return a pointer to the physical layer.
   */
  Ptr<LteEnbPhy> GetPhy (void) const;
  
  /** 
   * \return a pointer to the Radio Resource Control instance of the eNB
   */
  Ptr<LteEnbRrc> GetRrc () const;

  /** 
   * \return the Cell Identifier of this eNB
   */
  uint16_t GetCellId () const;

  /** 
   * \return the uplink bandwidth in RBs
   */
  uint8_t GetUlBandwidth () const;

  /** 
   * \param bw the uplink bandwidth in RBs
   */
  void SetUlBandwidth (uint8_t bw);

  /** 
   * \return the downlink bandwidth in RBs
   */
  uint8_t GetDlBandwidth () const;

  /** 
   * \param bw the downlink bandwidth in RBs
   */
  void SetDlBandwidth (uint8_t bw);


private:
  bool DoSend (Ptr<Packet> packet,
               const Mac48Address& source,
               const Mac48Address& dest,
               uint16_t protocolNumber);

  void DoReceive (Ptr<Packet> p);

  /** 
   * Several attributes (e.g., the bandwidth) are exported as
   * attributes of the LteEnbNetDevice from a user perspective,  but
   * are actually used also in other modules as well (the RRC, the
   * PHY, the scheduler...). This methods takes care of updating the
   * configuration of all modules so that their copy of the attribute
   * values is in sync with the one in the LteEnbNetDevice.
   */
  void UpdateConfig (void);  

  Ptr<LteEnbMac> m_mac;

  Ptr<LteEnbPhy> m_phy;

  Ptr<LteEnbRrc> m_rrc;

  Ptr<FfMacScheduler> m_scheduler;

  uint16_t m_cellId; /**< Cell Identifer. Part of the CGI, see TS 29.274, section 8.21.1  */ 

  static uint16_t m_cellIdCounter; 

  uint8_t m_dlBandwidth; /**< downlink bandwidth in RBs */
  uint8_t m_ulBandwidth; /**< uplink bandwidth in RBs */
  
};

} // namespace ns3

#endif /* LTE_ENB_NET_DEVICE_H */
