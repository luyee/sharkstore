_Pragma("once");

#include <map>
#include <string>
#include <vector>

#include <rocksdb/db.h>

#include "base/status.h"
#include "proto/gen/metapb.pb.h"

namespace sharkstore {
namespace dataserver {
namespace storage {

static const std::string kRangeMetaPrefix = "\x02";
static const std::string kRangeApplyPrefix = "\x03";
static const std::string kNodeIDKey = "\x04NodeID";

class MetaStore {
public:
    explicit MetaStore(const std::string& path);
    ~MetaStore();

    Status Open();

    MetaStore(const MetaStore&) = delete;
    MetaStore& operator=(const MetaStore&) = delete;
    MetaStore& operator=(const MetaStore&) volatile = delete;

    Status SaveNodeID(uint64_t node_id);
    Status GetNodeID(uint64_t* node_id);

    Status GetAllRange(std::vector<metapb::Range>* range_metas);
    Status AddRange(const metapb::Range& meta);
    Status BatchAddRange(const std::vector<metapb::Range>& range_metas);
    Status DelRange(uint64_t range_id);

    Status SaveApplyIndex(uint64_t range_id, uint64_t apply_index);
    Status LoadApplyIndex(uint64_t range_id, uint64_t* apply_index);
    Status DeleteApplyIndex(uint64_t range_id);

private:
    const std::string path_;
    rocksdb::WriteOptions write_options_;
    rocksdb::DB* db_ = nullptr;
};

}  // namespace storage
}  // namespace dataserver
}  // namespace sharkstore
