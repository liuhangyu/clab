#include "sql/ob_physical_plan.h"

#include "gtest/gtest.h"

using namespace oceanbase::common;
using namespace oceanbase::sql;

//char buf[] = {
//(char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x02, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
//(char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x05, (char)0xF5, (char)0xE1, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x05, (char)0xF5, (char)0xE1,
//(char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x04, (char)0x00, (char)0x00,
//(char)0x00, (char)0x01, (char)0x0D, (char)0x00, (char)0x00, (char)0x00, (char)0x01, (char)0x13, (char)0x07, (char)0x09, (char)0x10, (char)0x09, (char)0x11, (char)0x09, (char)0x12, (char)0x09,
//(char)0x13, (char)0x09, (char)0x14, (char)0x09, (char)0x15, (char)0x09, (char)0x16, (char)0x04, (char)0x18, (char)0x79, (char)0x71, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
//(char)0x00, (char)0x00, (char)0x01, (char)0x01, (char)0x10, (char)0x00, (char)0x00, (char)0x00, (char)0x06, (char)0x0C, (char)0x00, (char)0x00, (char)0x00, (char)0x75, (char)0x70, (char)0x64,
//(char)0x61, (char)0x74, (char)0x65, (char)0x73, (char)0x65, (char)0x72, (char)0x76, (char)0x65, (char)0x72, (char)0x11, (char)0x00, (char)0x00, (char)0x00, (char)0x06, (char)0x0C, (char)0x00,
//(char)0x00, (char)0x00, (char)0x31, (char)0x30, (char)0x2E, (char)0x32, (char)0x33, (char)0x32, (char)0x2E, (char)0x33, (char)0x36, (char)0x2E, (char)0x33, (char)0x33, (char)0x12, (char)0x00,
//(char)0x00, (char)0x00, (char)0x02, (char)0x95, (char)0x0C, (char)0x13, (char)0x00, (char)0x00, (char)0x00, (char)0x02, (char)0x9F, (char)0x0C, (char)0x14, (char)0x00, (char)0x00, (char)0x00,
//(char)0x01, (char)0x02, (char)0x15, (char)0x00, (char)0x00, (char)0x00, (char)0x06, (char)0x23, (char)0x00, (char)0x00, (char)0x00, (char)0x30, (char)0x2E, (char)0x34, (char)0x2E, (char)0x32,
//(char)0x2E, (char)0x31, (char)0x5F, (char)0x31, (char)0x35, (char)0x36, (char)0x30, (char)0x37, (char)0x28, (char)0x41, (char)0x75, (char)0x67, (char)0x20, (char)0x31, (char)0x35, (char)0x20,
//(char)0x32, (char)0x30, (char)0x31, (char)0x33, (char)0x20, (char)0x32, (char)0x30, (char)0x3A, (char)0x33, (char)0x32, (char)0x3A, (char)0x35, (char)0x32, (char)0x29, (char)0x16, (char)0x00,
//(char)0x00, (char)0x00, (char)0x1F, (char)0xFE, (char)0x0C
//};

char buf[] = {
(char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x01, (char)0x00, (char)0x00, (char)0x00, (char)0x02, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
(char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x05, (char)0xF5, (char)0xE1, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x05, (char)0xF5, (char)0xE1,
(char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x04, (char)0x00, (char)0x00,
(char)0x00, (char)0x01, (char)0x0D, (char)0x00, (char)0x00, (char)0x00, (char)0x01, (char)0x13, (char)0x02, (char)0xB9, (char)0x17, (char)0x10, (char)0xB9, (char)0x17, (char)0x11, (char)0x01,
(char)0x18, (char)0x2A, (char)0x0D, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x01, (char)0x01, (char)0x10, (char)0x00, (char)0x00, (char)0x00,
(char)0x01, (char)0x01, (char)0x11, (char)0x00, (char)0x00, (char)0x00, (char)0x1F, (char)0x0D, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x01,
(char)0x02, (char)0x10, (char)0x00, (char)0x00, (char)0x00, (char)0x01, (char)0x02, (char)0x11, (char)0x00, (char)0x00, (char)0x00, (char)0x1F, (char)0xFE, (char)0x0C
};

class ObPhysicalPlanTest : public ::testing::Test
{
};

TEST_F(ObPhysicalPlanTest, deserialize)
{
  ObPhyOperatorFactory factory;
  ModuleArena arena;

  ObPhysicalPlan plan;
  plan.set_allocator(&arena);
  plan.set_operator_factory(&factory);

  int64_t pos = 0;
  ASSERT_EQ(0, plan.deserialize(buf, sizeof(buf), pos));
  
}

int main(int argc, char **argv)
{
  ob_init_memory_pool();
  ::testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
