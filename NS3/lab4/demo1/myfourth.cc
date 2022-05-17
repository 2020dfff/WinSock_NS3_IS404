/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 */

#include "ns3/object.h"
#include "ns3/uinteger.h"
#include "ns3/traced-value.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/internet-module.h"
#include <iostream>

using namespace ns3;

int myIndex = 0;

class MyObject : public Object
{
public:
  /**
   * Register this type.
   * \return The TypeId.
   */
  static TypeId GetTypeId (void)
  {
    static TypeId tid = TypeId ("MyObject")
      .SetParent<Object> ()
      .SetGroupName ("Tutorial")
      .AddConstructor<MyObject> ()
      .AddTraceSource ("MyInteger",
                       "An integer value to trace.",
                       MakeTraceSourceAccessor (&MyObject::m_myInt),
                       "ns3::TracedValueCallback::Int32")
    ;
    return tid;
  }

  MyObject () {}
  TracedValue<int32_t> m_myInt;
};

void
IntTrace (int32_t oldValue, int32_t newValue)
{
  std::cout << "Traced " << oldValue << " to " << newValue << std::endl;
}

static void
IntRecord (Ptr<OutputStreamWrapper> stream, int32_t oldValue, int32_t newValue)
{
  		*stream->GetStream () << myIndex << "\t" << newValue << std::endl;
}


int
main (int argc, char *argv[])
{
  Ptr<MyObject> myObject = CreateObject<MyObject> ();
  
  std::string filename = "myfourth.dat";
  std::ios::openmode filemode = std::ios::out;
  Ptr<OutputStreamWrapper> stream = Create<OutputStreamWrapper>(filename, filemode);
  myObject->TraceConnectWithoutContext ("MyInteger", MakeCallback (&IntTrace));
  myObject->TraceConnectWithoutContext ("MyInteger", MakeBoundCallback(&IntRecord, stream));

  //myObject->TraceConnectWithoutContext ("MyInteger", MakeCallback (&IntTrace));
  //myObject->m_myInt = 1234;
        for ( myIndex = 0 ; myIndex < 10; myIndex++) {
                myObject->m_myInt = myIndex * myIndex;
  }
}



