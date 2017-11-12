#ifndef FIBONACCI_H
#define FIBONACCI_H
#include <stack>

int fibRec (int n)
{
    if (n <= 2)
    {
        return 1;
    }
    int prev = fibRec(n-1);
    int prev2 = fibRec(n-2);
    int result = prev + prev2;
    return result;
}

struct FibStackFrame
{
    int n;
    int prev;
    int prev2;
    bool hasPrev;
    bool hasPrev2;
    FibStackFrame():n(0), prev(0), prev2(0),
        hasPrev(false), hasPrev2(false) {}
};

/**
 * Each FibStackFrame represents a single call to the fibRec function.
 * We track where we are in the function execution with the hasPrev and hasPrev2 flags.
 * When both prev and prev2 are calculated, the frame is completed (we have the final result)
 * and we pop the frame from the stack.
 */
int fibStack(int n)
{
    std::stack<FibStackFrame> st;
    FibStackFrame first;
    first.n = n;
    st.push(first);
    while(!st.empty())
    {
        FibStackFrame topFrame = st.top();
        // check if we are ready to calculate the result for topFrame
        if (topFrame.n <= 2 || (topFrame.hasPrev && topFrame.hasPrev2))
        {
            // this corresponds to return parts of the recursive function
            int topResult = topFrame.n <= 2? 1 : topFrame.prev + topFrame.prev2;
            st.pop();
            if (st.empty())
            {
                // we have completed the final Fib computation in the stack,
                // so this is the final result
                return topResult;
            }
            // else we need to "return" topResult to the stack frame that invoked it,
            // which is now at the top of our stack.
            // we need reference here, because we want to modify the actual frame
            // on top of the stack, not its copy
            FibStackFrame& parentFrame = st.top();
            if (!parentFrame.hasPrev)
            {
                parentFrame.prev = topResult;
                parentFrame.hasPrev = true;
            }
            else
            {
                parentFrame.prev2 = topResult;
                parentFrame.hasPrev2 = true;
            }

        }
        else if (!topFrame.hasPrev)
        {
            FibStackFrame prevCalc;
            prevCalc.n = topFrame.n - 1;
            st.push(prevCalc);
        }
        else if (!topFrame.hasPrev2)
        {
            FibStackFrame prevCalc;
            prevCalc.n = topFrame.n - 2;
            st.push(prevCalc);
        }
    }
}
#endif // FIBONACCI_H

