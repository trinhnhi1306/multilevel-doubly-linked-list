#include <gtest/gtest.h>
#include "LinkedList.h"
#include <vector>
#include <string>

// Helper function to convert linked list to a vector of strings
std::vector<std::string> listToVector(Node* head) {
    std::vector<std::string> result;
    Node* curr = head;
    while (curr) {
        result.push_back(curr->header);
        curr = curr->next;
    }
    return result;
}

class FlattenTest : public ::testing::Test {
protected:
    Node* head;

    void SetUp() override {
        readFileToList(head, "/mnt/f/c_plus_plus_exercise/multilevel-doubly-linked-list/sample.txt"); // Read the file to create the linked list
    }

    void TearDown() override {
        freeList(head); // Free memory
    }
};

// Test case for verifying flattening
TEST_F(FlattenTest, FlattenAndVerify) {
    // Flatten the linked list
    Node* result = flatten(head);

    // Convert to vector for comparison
    std::vector<std::string> flattenedList = listToVector(result);
    std::vector<std::string> expectedList = { 
        "Header1", "Header1.1", "Header1.2", "Header2", 
        "Header2.1", "Header2.2", "Header2.2.1", "Header3", "Header4", 
        "Header4.1", "Header4.1.1"
    };

    EXPECT_EQ(flattenedList, expectedList);
}

// Test case for verifying flattening
TEST_F(FlattenTest, BadFunctionTest) {
    Node* testHead = new Node("header", "data");
    // Call badFunction
    badFunction(testHead);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}