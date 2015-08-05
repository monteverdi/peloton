//===----------------------------------------------------------------------===//
//
//							PelotonDB
//
// order_by_node.h
//
// Identification: src/backend/planner/order_by_node.h
//
// Copyright (c) 2015, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//


#pragma once

#include <memory>
#include <string>
#include <vector>

#include "backend/common/types.h"
#include "backend/expression/abstract_expression.h"
#include "backend/planner/abstract_plan_node.h"

namespace peloton {
namespace planner {

/**
 * IMPORTANT All tiles got from child must have the same physical schema.
 */

class OrderByNode : public AbstractPlanNode {
 public:
  OrderByNode(const OrderByNode&) = delete;
  OrderByNode& operator=(const OrderByNode&) = delete;
  OrderByNode(const OrderByNode&&) = delete;
  OrderByNode& operator=(const OrderByNode&&) = delete;

  OrderByNode(const std::vector<oid_t>& sort_keys,
              const std::vector<bool>& descend_flags,
              const std::vector<oid_t>& output_column_ids,
              storage::AbstractBackend* backend)
      : sort_keys_(sort_keys),
        descend_flags_(descend_flags),
        output_column_ids_(output_column_ids),
        backend_(backend) {}

  //  OrderByNode(
  //        const std::vector<oid_t>  &sort_keys,
  //        const std::vector<bool>   &descend_flags,
  //        const std::vector<oid_t>  &output_column_ids)
  //    : sort_keys_(sort_keys),
  //      descend_flags_(descend_flags),
  //      output_column_ids_(output_column_ids) {
  //    backend_ = new storage::VMBackend();
  //  }

  storage::AbstractBackend* GetBackend() const { return backend_; }

  const std::vector<oid_t>& GetSortKeys() const { return sort_keys_; }

  const std::vector<bool>& GetDescendFlags() const { return descend_flags_; }

  const std::vector<oid_t>& GetOutputColumnIds() const {
    return output_column_ids_;
  }

  inline PlanNodeType GetPlanNodeType() const { return PLAN_NODE_TYPE_ORDERBY; }

  inline std::string GetInfo() const { return "OrderBy"; }

 private:
  /** @brief Column Ids to sort keys w.r.t input tiles.
   *  Primary sort key comes first, secondary comes next, etc.
   */
  const std::vector<oid_t> sort_keys_;

  /** @brief Sort order flags. */
  const std::vector<bool> descend_flags_;

  /** @brief Projected columns Ids.
   * TODO Not used now.
   * Now we just output the same schema as input tiles.
   */
  const std::vector<oid_t> output_column_ids_;

  /** @brief Backend used to allocate intermediate physical tiles. */
  storage::AbstractBackend* backend_;
};
}
}
