#ifndef STRINGEDITOR_H
#define STRINGEDITOR_H
#include <string>
#include <stack>
class StringEditor
{
    public:
        StringEditor(const std::string& = "");
        virtual ~StringEditor();
        void insert(const std::string&, int=0);
        void remove(int from, int to);
        std::string getText() const;
        void undo();
        void redo();
    protected:

    private:
        std::string text;
        std::stack<std::string> undoStack;
        std::stack<std::string> redoStack;
        void emptyRedoStack();
};

#endif // STRINGEDITOR_H
