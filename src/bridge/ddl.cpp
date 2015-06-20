/*-------------------------------------------------------------------------
 *
 * dll.cpp
 * file description
 *
 * Copyright(c) 2015, CMU
 *
 * /n-store/src/bridge/ddl.cpp
 *
 *-------------------------------------------------------------------------
 */

#include "bridge/ddl.h"
#include "executor/create_executor.h"
#include "parser/parser.h"
#include "parser/statement_create.h"

namespace nstore {
namespace bridge {

int DDL::CreateTable(int arg){
    // FIXME: Get default db 
    catalog::Database* db = catalog::Catalog::GetInstance().GetDatabase(DEFAULT_DB_NAME);
    assert(db);

    parser::CreateStatement* stmt;
    stmt->name = "tbname"; // warning
    executor::CreateExecutor::CreateTable(db, stmt); 
    return arg * 2;
}

extern "C" int DDL_CreateTable(int arg) {
    return DDL::CreateTable(arg);
}

} // namespace bridge
} // namespace nstore
