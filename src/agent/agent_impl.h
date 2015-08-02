// Copyright (c) 2015, Baidu.com, Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef _AGENT_IMPL_H_
#define _AGENT_IMPL_H_

#include <string>
#include <map>

#include "sofa/pbrpc/pbrpc.h"
#include "proto/agent.pb.h"
#include "proto/master.pb.h"
#include "proto/gced.pb.h"

#include "mutex.h"
#include "thread_pool.h"
#include "rpc/rpc_client.h"

namespace baidu {
namespace galaxy {

class AgentImpl : public Agent {

public:
    AgentImpl();
    virtual ~AgentImpl(); 

    bool Init();

    virtual void Query(::google::protobuf::RpcController* cntl, 
                       const ::baidu::galaxy::QueryRequest* req,
                       ::baidu::galaxy::QueryResponse* resp,
                       ::google::protobuf::Closure* done); 
    virtual void RunPod(::google::protobuf::RpcController* cntl,
                        const ::baidu::galaxy::RunPodRequest* req,
                        ::baidu::galaxy::RunPodResponse* resp,
                        ::google::protobuf::Closure* done);
    virtual void KillPod(::google::protobuf::RpcController* cntl,
                         const ::baidu::galaxy::KillPodRequest* req,
                         ::baidu::galaxy::KillPodResponse* resp,
                         ::google::protobuf::Closure* done);
private:
    void KeepHeartBeat();
    
    bool RegistToMaster();
    bool CheckGcedConnection();

    bool PingMaster();

    //void ParseVolumeInfoFromString(const std::string& volume_str,                                   std::vector<Volume>* volumes);

    //void ConvertResourceToPb(const ResourceCapacity& resource, Resource* resource_pb);
private:
    std::string master_endpoint_;
    std::string gce_endpoint_; 
    
    Mutex lock_;
    ThreadPool background_threads_;
    RpcClient* rpc_client_;
    std::string endpoint_;
    Master_Stub* master_;
    Gced_Stub* gced_;
};

}   // ending namespace galaxy
}   // ending namespace baidu


#endif