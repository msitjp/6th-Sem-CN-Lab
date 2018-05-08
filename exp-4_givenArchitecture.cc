#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer hosts;
  NodeContainer routers;

  hosts.Create (1);
  routers.Create (4);

  InternetStackHelper stack;

  Ipv4AddressHelper address;

  stack.Install (routers);
  stack.Install (hosts);

  PointToPointHelper p1,p2,p3,p4;

  NodeContainer subnet1;
  subnet1. Add(hosts.Get (0));
 subnet1. Add(routers.Get (0));

NetDeviceContainer subnet1devices=p1.Install (subnet1);
  address.SetBase ("10.1.1.0", "255.255.255.0");

Ipv4InterfaceContainer interfaces = address.Assign (subnet1devices);

NodeContainer subnet2;
  subnet2. Add(routers.Get (0));
 subnet2. Add(routers.Get (1));

NetDeviceContainer subnet2devices=p2.Install (subnet2);
  address.SetBase ("10.1.2.0", "255.255.255.0");

interfaces = address.Assign (subnet2devices);


NodeContainer subnet3;
  subnet3. Add(routers.Get (1));
 subnet3. Add(routers.Get (2));

NetDeviceContainer subnet3devices=p3.Install (subnet3);
  address.SetBase ("10.1.3.0", "255.255.255.0");

interfaces = address.Assign (subnet3devices);

NodeContainer subnet4;
  subnet4. Add(routers.Get (2));
 subnet4. Add(routers.Get (3));

NetDeviceContainer subnet4devices=p4.Install (subnet4);
  address.SetBase ("10.1.4.0", "255.255.255.0");

interfaces = address.Assign (subnet4devices);

  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (routers.Get (3));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));


  ApplicationContainer clientApps = echoClient.Install (hosts.Get (0));

  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  AnimationInterface anim("animations/given_architecture.xml");

  anim.SetConstantPosition(hosts.Get(0),1.0,2.0);
  anim.SetConstantPosition(routers.Get(0),2.0,3.0);
  anim.SetConstantPosition(routers.Get(1),3.0,4.0);
  anim.SetConstantPosition(routers.Get(2),4.0,5.0);
  anim.SetConstantPosition(routers.Get(3),5.0,6.0);
    Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}