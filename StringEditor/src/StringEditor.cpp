#include "StringEditor.h"

StringEditor::StringEditor(const std::string& initialText)
 : text(initialText) {
    //ctor
}

StringEditor::~StringEditor()
{
    //dtor
}

void StringEditor::emptyRedoStack() {
    while(!redoStack.empty()) {
        redoStack.pop();
    }
}
void StringEditor::insert(const std::string& newText, int startPos) {
    undoStack.push(text);
    emptyRedoStack();
    text.insert(startPos, newText);
}

// StringEditor::remove ���� �� ������� from �� ������� to (��� to)
void StringEditor::remove(int from, int to) {
    // string::erase ���� �� ������� n �� ���� �������
    undoStack.push(text);
    emptyRedoStack();
    text.erase(from, to - from);
}

std::string StringEditor::getText() const {
    return text;
}
void StringEditor::undo() {
    if (!undoStack.empty()) {
        std::string oldText = undoStack.top();
        undoStack.pop();
        redoStack.push(text);
        text = oldText;
    }
}
void StringEditor::redo() {
    if (!redoStack.empty()) {
        std::string textToRedo = redoStack.top();
        redoStack.pop();
        undoStack.push(text);
        text = textToRedo;
    }
}
