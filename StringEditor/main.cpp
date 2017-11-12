#include <iostream>
#include <cstring>
// You should clone https://github.com/triffon/oop-unit-test-framework
// in a folder next to your project's in order for the imports to work
// (it is included as a submodule to this github repository)
#include "../oop-unit-test-framework/UnitTestFramework.h"
#include "StringEditor.h"
#include <stack>

TEST_CASE("StringEditor", UndoOnce) {
    StringEditor editor;
    editor.insert("Hello!");
    editor.undo();
    Assert::AreEqual(editor.getText(), "");
}

TEST_CASE("StringEditor", UndoRedoOnce) {
    StringEditor editor;
    editor.insert("Hello!");
    editor.undo();
    editor.redo();
    Assert::AreEqual(editor.getText(), "Hello!");
}


TEST_CASE("StringEditor", UndoRedoUndo) {
    StringEditor editor;
    editor.insert("Hello!");
    editor.insert("World", 5);
    editor.insert(" FMI", strlen("HelloWorld"));
    editor.undo();
    editor.redo();
    editor.undo();
    Assert::AreEqual(editor.getText(), "HelloWorld!");
}

TEST_CASE("StringEditor", UndoNoOp) {
    StringEditor editor("Hello, World!");
    editor.undo();
    Assert::AreEqual(editor.getText(), "Hello, World!");
}

TEST_CASE("StringEditor", RedoNoOp) {
    StringEditor editor("Hello, World!");
    editor.redo();
    Assert::AreEqual(editor.getText(), "Hello, World!");
}

TEST_CASE("StringEditor", MultipleUndo) {
    StringEditor editor;
    editor.insert("Hello");
    editor.insert("World");
    editor.undo();
    editor.undo();
    Assert::AreEqual(editor.getText(), "");
}

TEST_CASE("StringEditor", MultipleUndoRedo) {
    StringEditor editor;
    editor.insert("Hello");
    editor.insert("World");
    editor.undo();
    editor.undo();
    editor.redo();
    editor.redo();
    Assert::AreEqual(editor.getText(), "WorldHello");
}

TEST_CASE("StringEditor", RedoAfterInsert) {
    StringEditor editor;
    editor.insert("Hello!");
    editor.undo();
    editor.insert("World!");
    editor.redo();
    Assert::AreEqual(editor.getText(), "World!");
}

TEST_CASE("StringEditor", InsertText) {
    StringEditor editor;
    editor.insert("Hello!");
    Assert::AreEqual(editor.getText(), "Hello!");
}

TEST_CASE("StringEditor", InsertTextMiddle) {
    StringEditor editor;
    editor.insert("Hello!");
    editor.insert(", World", strlen("Hello"));
    Assert::AreEqual(editor.getText(), "Hello, World!");
}

TEST_CASE("StringEditor", RemoveText) {
    StringEditor editor;
    editor.insert("Hello, World!");
    editor.remove(strlen("Hello"), strlen("Hello, World"));
    std::cout << editor.getText() << std::endl;
    Assert::AreEqual(editor.getText(), "Hello!");
}

int main()
{
    RunTests();
    return 0;
}
