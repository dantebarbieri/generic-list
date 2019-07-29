#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <netinet/in.h>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include "LinkedList.hpp"
#include "Node.hpp"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class TestLists : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(TestLists);
  CPPUNIT_TEST(testNodeConstructor);
  CPPUNIT_TEST(testLinkedListEquality);
  CPPUNIT_TEST(testLinkedListIsEmpty);
  CPPUNIT_TEST(testLinkedListGetHead);
  CPPUNIT_TEST(testLinkedListLength);
  CPPUNIT_TEST(testLinkedListAppend);
  CPPUNIT_TEST(testLinkedListPrepend);
  CPPUNIT_TEST(testLinkedListInsert);
  CPPUNIT_TEST(testLinkedListOutput);
  CPPUNIT_TEST(testLinkedListAccess);
  CPPUNIT_TEST(testLinkedListRemoveSingle);
  CPPUNIT_TEST(testLinkedListRemoveMultiple);
  CPPUNIT_TEST_SUITE_END();

 protected:
  void testNodeConstructor(void);
  void testLinkedListEquality(void);
  void testLinkedListIsEmpty(void);
  void testLinkedListGetHead(void);
  void testLinkedListLength(void);
  void testLinkedListAppend(void);
  void testLinkedListPrepend(void);
  void testLinkedListInsert(void);
  void testLinkedListOutput(void);
  void testLinkedListAccess(void);
  void testLinkedListRemoveSingle(void);
  void testLinkedListRemoveMultiple(void);
};

//-----------------------------------------------------------------------------

void TestLists::testNodeConstructor(void) {
  Node<int> a(1);
  Node<string> b("A");
  CPPUNIT_ASSERT(1 == a.data);
  CPPUNIT_ASSERT("A" == b.data);
  CPPUNIT_ASSERT(nullptr == a.next);
  CPPUNIT_ASSERT(nullptr == b.next);
}

void TestLists::testLinkedListEquality(void) {
  const LinkedList<int> a;
  const LinkedList<string> b;
  const LinkedList<int> c(1);
  const LinkedList<string> d("A");
  const LinkedList<int> e({1, 1});
  const LinkedList<string> f({"A", "A"});
  CPPUNIT_ASSERT(a == a);
  CPPUNIT_ASSERT(b == b);
  CPPUNIT_ASSERT(a == LinkedList<int>());
  CPPUNIT_ASSERT(a != LinkedList<int>(1));
  CPPUNIT_ASSERT(c == LinkedList<int>(1));
  CPPUNIT_ASSERT(c != LinkedList<int>());
  CPPUNIT_ASSERT(c != LinkedList<int>(2));
  CPPUNIT_ASSERT(c != LinkedList<int>({1, 1}));
  CPPUNIT_ASSERT(e == LinkedList<int>({1, 1}));
  CPPUNIT_ASSERT(e != LinkedList<int>({1, 2}));
  CPPUNIT_ASSERT(e != LinkedList<int>({2, 1}));
  CPPUNIT_ASSERT(e != LinkedList<int>({2, 2}));
  CPPUNIT_ASSERT(b == LinkedList<string>());
  CPPUNIT_ASSERT(b != LinkedList<string>("A"));
  CPPUNIT_ASSERT(d == LinkedList<string>("A"));
  CPPUNIT_ASSERT(d != LinkedList<string>());
  CPPUNIT_ASSERT(d != LinkedList<string>("B"));
  CPPUNIT_ASSERT(d != LinkedList<string>({"A", "A"}));
  CPPUNIT_ASSERT(f == LinkedList<string>({"A", "A"}));
  CPPUNIT_ASSERT(f != LinkedList<string>({"A", "B"}));
  CPPUNIT_ASSERT(f != LinkedList<string>({"B", "A"}));
  CPPUNIT_ASSERT(f != LinkedList<string>({"B", "B"}));
}

void TestLists::testLinkedListIsEmpty(void) {
  CPPUNIT_ASSERT(LinkedList<int>().isEmpty());
  CPPUNIT_ASSERT(!LinkedList<int>(1).isEmpty());
  CPPUNIT_ASSERT(!LinkedList<int>({1, 2}).isEmpty());
}

void TestLists::testLinkedListGetHead(void) {
  CPPUNIT_ASSERT(1 == LinkedList<int>(1).getHead());
  CPPUNIT_ASSERT_THROW(LinkedList<int>().getHead(), exception);
  CPPUNIT_ASSERT(1 == LinkedList<int>({1, 2}).getHead());
  CPPUNIT_ASSERT(2 == LinkedList<int>({2, 1}).getHead());
  CPPUNIT_ASSERT("A" == LinkedList<string>("A").getHead());
  CPPUNIT_ASSERT_THROW(LinkedList<string>().getHead(), exception);
  CPPUNIT_ASSERT("A" == LinkedList<string>({"A", "B"}).getHead());
  CPPUNIT_ASSERT("B" == LinkedList<string>({"B", "A"}).getHead());
}

void TestLists::testLinkedListLength(void) {
  CPPUNIT_ASSERT(0 == LinkedList<int>().length());
  CPPUNIT_ASSERT(1 == LinkedList<int>(1).length());
  CPPUNIT_ASSERT(2 == LinkedList<int>({1, 1}).length());
  CPPUNIT_ASSERT(2 == LinkedList<int>({1, 2}).length());
  CPPUNIT_ASSERT(0 == LinkedList<string>().length());
  CPPUNIT_ASSERT(1 == LinkedList<string>("A").length());
  CPPUNIT_ASSERT(2 == LinkedList<string>({"A", "A"}).length());
  CPPUNIT_ASSERT(2 == LinkedList<string>({"B", "B"}).length());
}

void TestLists::testLinkedListAppend(void) {
  LinkedList<int> a;
  LinkedList<string> b;
  CPPUNIT_ASSERT(LinkedList<int>(1) == a.append(1));
  CPPUNIT_ASSERT(LinkedList<int>({1, 2}) == a.append(2));
  CPPUNIT_ASSERT(LinkedList<string>("A") == b.append("A"));
  CPPUNIT_ASSERT(LinkedList<string>({"A", "B"}) == b.append("B"));
}

void TestLists::testLinkedListPrepend(void) {
  LinkedList<int> a;
  LinkedList<string> b;
  CPPUNIT_ASSERT(LinkedList<int>(1) == a.prepend(1));
  CPPUNIT_ASSERT(LinkedList<int>({2, 1}) == a.prepend(2));
  CPPUNIT_ASSERT(LinkedList<string>("A") == b.prepend("A"));
  CPPUNIT_ASSERT(LinkedList<string>({"B", "A"}) == b.prepend("B"));
}

void TestLists::testLinkedListInsert(void) {
  LinkedList<int> a;
  LinkedList<string> b;
  CPPUNIT_ASSERT(LinkedList<int>(1) == a.insert(1, 0));
  CPPUNIT_ASSERT(LinkedList<int>({0, 1}) == a.insert(0, 0));
  CPPUNIT_ASSERT(LinkedList<int>({0, 1, 3}) == a.insert(3, 2));
  CPPUNIT_ASSERT(LinkedList<int>({0, 1, 2, 3}) == a.insert(2, 2));
  CPPUNIT_ASSERT(LinkedList<string>("A") == b.insert("A", 0));
  CPPUNIT_ASSERT(LinkedList<string>({" ", "A"}) == b.insert(" ", 0));
  CPPUNIT_ASSERT(LinkedList<string>({" ", "A", "C"}) == b.insert("C", 2));
  CPPUNIT_ASSERT(LinkedList<string>({" ", "A", "B", "C"}) == b.insert("B", 2));
}

void TestLists::testLinkedListOutput(void) {
  std::stringstream output;
  output << LinkedList<int>();
  CPPUNIT_ASSERT("[]" == output.str());
  output.str(std::string());
  output << LinkedList<int>(1);
  CPPUNIT_ASSERT("[1]" == output.str());
  output.str(std::string());
  output << LinkedList<int>({1, 2});
  CPPUNIT_ASSERT("[1->2]" == output.str());
  output.str(std::string());
  output << LinkedList<int>({1, 2, 3});
  CPPUNIT_ASSERT("[1->2->3]" == output.str());
  output.str(std::string());
  output << LinkedList<string>();
  CPPUNIT_ASSERT("[]" == output.str());
  output.str(std::string());
  output << LinkedList<string>("A");
  CPPUNIT_ASSERT("[A]" == output.str());
  output.str(std::string());
  output << LinkedList<string>({"A", "B"});
  CPPUNIT_ASSERT("[A->B]" == output.str());
  output.str(std::string());
  output << LinkedList<string>({"A", "B", "C"});
  CPPUNIT_ASSERT("[A->B->C]" == output.str());
  output.str(std::string());
}

void TestLists::testLinkedListAccess(void) {
  const LinkedList<int> a({1, 2});
  const LinkedList<string> b({"A", "B"});
  CPPUNIT_ASSERT(a[0] == 1);
  CPPUNIT_ASSERT(a[1] == 2);
  CPPUNIT_ASSERT_THROW(a[2], exception);
  CPPUNIT_ASSERT(b[0] == "A");
  CPPUNIT_ASSERT(b[1] == "B");
  CPPUNIT_ASSERT_THROW(a[2], exception);
}

void TestLists::testLinkedListRemoveSingle(void) {
  LinkedList<int> a({1, 2, 3, 2, 1});
  int b;
  LinkedList<string> c({"A", "B", "C", "B", "A"});
  string d;
  b = a.remove(2);
  CPPUNIT_ASSERT(a == LinkedList<int>({1, 2, 2, 1}));
  CPPUNIT_ASSERT(b == 3);
  b = a.remove(2);
  CPPUNIT_ASSERT(a == LinkedList<int>({1, 2, 1}));
  CPPUNIT_ASSERT(b == 2);
  b = a.remove(0);
  CPPUNIT_ASSERT(a == LinkedList<int>({2, 1}));
  CPPUNIT_ASSERT(b == 1);
  b = a.remove(1);
  CPPUNIT_ASSERT(a == LinkedList<int>(2));
  CPPUNIT_ASSERT(b == 1);
  CPPUNIT_ASSERT_THROW(a.remove(1), exception);
  b = a.remove(0);
  CPPUNIT_ASSERT(a == LinkedList<int>());
  CPPUNIT_ASSERT(b == 2);
  CPPUNIT_ASSERT_THROW(a.remove(0), exception);
  d = c.remove(2);
  CPPUNIT_ASSERT(c == LinkedList<string>({"A", "B", "B", "A"}));
  CPPUNIT_ASSERT(d == "C");
  d = c.remove(2);
  CPPUNIT_ASSERT(c == LinkedList<string>({"A", "B", "A"}));
  CPPUNIT_ASSERT(d == "B");
  d = c.remove(0);
  CPPUNIT_ASSERT(c == LinkedList<string>({"B", "A"}));
  CPPUNIT_ASSERT(d == "A");
  d = c.remove(1);
  CPPUNIT_ASSERT(c == LinkedList<string>("B"));
  CPPUNIT_ASSERT(d == "A");
  CPPUNIT_ASSERT_THROW(c.remove(1), exception);
  d = c.remove(0);
  CPPUNIT_ASSERT(c == LinkedList<string>());
  CPPUNIT_ASSERT(d == "B");
  CPPUNIT_ASSERT_THROW(c.remove(0), exception);
}

void TestLists::testLinkedListRemoveMultiple(void) {
  LinkedList<int> a({1, 1, 1, 2, 2, 2, 3, 3});
  LinkedList<string> b({"A", "A", "A", "B", "B", "B", "C", "C"});
  CPPUNIT_ASSERT(LinkedList<int>({1, 1, 1, 2, 2, 2, 3, 3}) == a.remove(4, 1));
  CPPUNIT_ASSERT(LinkedList<int>({1, 1, 1, 2, 2, 2, 3}) == a.remove(3, 1));
  CPPUNIT_ASSERT(LinkedList<int>({1, 1, 1, 2, 2, 2, 3}) == a.remove(3, 0));
  CPPUNIT_ASSERT(LinkedList<int>({1, 1, 1, 2, 2, 2}) == a.remove(3, 1));
  CPPUNIT_ASSERT(LinkedList<int>({1, 2, 2, 2}) == a.remove(1, 2));
  CPPUNIT_ASSERT(LinkedList<int>({2, 2, 2}) == a.remove(1, 2));
  CPPUNIT_ASSERT(LinkedList<int>({}) == a.remove(2, -1));
  CPPUNIT_ASSERT(LinkedList<int>({}) == a.remove(0, 1));
  CPPUNIT_ASSERT(LinkedList<string>({"A", "A", "A", "B", "B", "B", "C", "C"}) == b.remove("D", 1));
  CPPUNIT_ASSERT(LinkedList<string>({"A", "A", "A", "B", "B", "B", "C"}) == b.remove("C", 1));
  CPPUNIT_ASSERT(LinkedList<string>({"A", "A", "A", "B", "B", "B", "C"}) == b.remove("C", 0));
  CPPUNIT_ASSERT(LinkedList<string>({"A", "A", "A", "B", "B", "B"}) == b.remove("C", 1));
  CPPUNIT_ASSERT(LinkedList<string>({"A", "B", "B", "B"}) == b.remove("A", 2));
  CPPUNIT_ASSERT(LinkedList<string>({"B", "B", "B"}) == b.remove("A", 2));
  CPPUNIT_ASSERT(LinkedList<string>({}) == b.remove("B", -1));
  CPPUNIT_ASSERT(LinkedList<string>({}) == b.remove(" ", 1));
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION(TestLists);

int main(int argc, char* argv[]) {
  // informs test-listener about testresults
  CPPUNIT_NS::TestResult testresult;

  // register listener for collecting the test-results
  CPPUNIT_NS::TestResultCollector collectedresults;
  testresult.addListener(&collectedresults);

  // register listener for per-test progress output
  CPPUNIT_NS::BriefTestProgressListener progress;
  testresult.addListener(&progress);

  // insert test-suite at test-runner by registry
  CPPUNIT_NS::TestRunner testrunner;
  testrunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  testrunner.run(testresult);

  // output results in compiler-format
  CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
  compileroutputter.write();

  // Output XML for Jenkins CPPunit plugin
  ofstream xmlFileOut("cppTestListsResults.xml");
  XmlOutputter xmlOut(&collectedresults, xmlFileOut);
  xmlOut.write();

  // return 0 if tests were successful
  return collectedresults.wasSuccessful() ? 0 : 1;
}
