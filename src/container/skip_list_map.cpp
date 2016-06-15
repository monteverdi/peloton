//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// skip_list_map.cpp
//
// Identification: src/container/skip_list_map.cpp
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <functional>
#include <iostream>

#include "container/skip_list_map.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/types.h"

namespace peloton {

SKIP_LIST_MAP_TEMPLATE_ARGUMENTS
SKIP_LIST_MAP_TYPE::SkipListMap(){
}

SKIP_LIST_MAP_TEMPLATE_ARGUMENTS
SKIP_LIST_MAP_TYPE::~SkipListMap(){
}

SKIP_LIST_MAP_TEMPLATE_ARGUMENTS
bool SKIP_LIST_MAP_TYPE::Insert(const KeyType &key, ValueType value){
  auto status = skip_list_map.insert(key, value);
  LOG_TRACE("insert status : %d", status);
  return status;
}

SKIP_LIST_MAP_TEMPLATE_ARGUMENTS
bool SKIP_LIST_MAP_TYPE::Update(const KeyType &key, ValueType value){

  const bool bInsert = true;
  auto status =  skip_list_map.update(key, [&value]( bool bNew, map_pair& found_pair) {
    if(bNew == true) {
      // new entry
      LOG_INFO("New entry");
    }
    else {
      // found existing entry
      found_pair.second = value;
      LOG_INFO("Updating existing entry");
    }
  }, bInsert);

  return status.first;
}

SKIP_LIST_MAP_TEMPLATE_ARGUMENTS
bool SKIP_LIST_MAP_TYPE::Erase(const KeyType &key){

  auto status = skip_list_map.erase(key);
  LOG_TRACE("erase status : %d", status);

  return status;
}

SKIP_LIST_MAP_TEMPLATE_ARGUMENTS
bool SKIP_LIST_MAP_TYPE::Find(const KeyType &key,
                              ValueType& value){

  auto status = skip_list_map.find(key, [&value]( map_pair& found_value) {
    value = found_value.second;
  } );

  LOG_TRACE("find status : %d", status);
  return status;
}

SKIP_LIST_MAP_TEMPLATE_ARGUMENTS
bool SKIP_LIST_MAP_TYPE::Contains(const KeyType &key){
  return skip_list_map.contains(key);
}

SKIP_LIST_MAP_TEMPLATE_ARGUMENTS
void SKIP_LIST_MAP_TYPE::Clear(){
  skip_list_map.clear();
}

SKIP_LIST_MAP_TEMPLATE_ARGUMENTS
size_t SKIP_LIST_MAP_TYPE::GetSize() const{
  return skip_list_map.size();
}

SKIP_LIST_MAP_TEMPLATE_ARGUMENTS
bool SKIP_LIST_MAP_TYPE::IsEmpty() const{
  return skip_list_map.empty();
}

// Explicit template instantiation
template class SkipListMap<uint32_t, uint32_t>;

}  // End peloton namespace
