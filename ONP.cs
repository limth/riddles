using System;
using System.Collections.Generic;
using System.Text;

namespace ONP
{
    class Program
    {
        public const char LEFT_PARENTHESIS = '(';
        public const char RIGHT_PARENTHESIS = ')';
        public const char CARET = '^';

        private static byte T;
        private static StringBuilder output = new StringBuilder();
        private static Stack<char> stack = new Stack<char>();

        private static Dictionary<char, byte> OPERATORS = new Dictionary<char, byte>()
        {
            {'^', 4 },
            {'*', 3 },
            {'/', 3 },
            {'+', 2 },
            {'-', 2 },
            {'(', 1 },
            {')', 1 }
        };

        static void Main(string[] args)
        {
            T = byte.Parse(Console.ReadLine());

            for (byte l = 0; l < T; l++)
            {
                var input = Console.ReadLine();

                for (int i = 0; i < input.Length; i++)
                {
                    var literal = input[i];
                    if (IsAnOperand(literal))
                    {
                        output.Append(literal);
                        continue;
                    }
                    else if (IsAnOperator(literal))
                    {
                        if (IsLeftParenthesis(literal))
                        {
                            stack.Push(literal);
                            continue;
                        }
                        else if (IsRightParenthesis(literal))
                        {
                            var poppedOp = stack.Pop();
                            while (!IsLeftParenthesis(poppedOp))
                            {
                                output.Append(poppedOp);

                                poppedOp = stack.Pop();
                            }

                            continue;
                        }

                        char peekedOp = '_';
                        if (stack.Count > 0)
                        {
                            peekedOp = stack.Peek();
                        }

                        if (peekedOp != '_')
                        {
                            if (IsACaret(literal))
                            {
                                if (OPERATORS[literal] < OPERATORS[peekedOp])
                                {
                                    output.Append(stack.Pop());
                                }
                            }

                            if (OPERATORS[literal] <= OPERATORS[peekedOp])
                            {
                                output.Append(stack.Pop());
                            }
                        }

                        stack.Push(literal);
                    }
                }

                output.Append(stack.ToArray());

                Console.WriteLine(output.ToString());
                output = new StringBuilder();
            }
        }

        private static bool IsAnOperator(char x)
        {
            if (Contains(OPERATORS.Keys, x))
            {
                return true;
            }

            return false;
        }

        private static bool IsAnOperand(char x)
        {
            if (!Contains(OPERATORS.Keys, x))
            {
                return true;
            }

            return false;
        }

        private static bool IsLeftParenthesis(char x)
        {
            if (x == LEFT_PARENTHESIS)
            {
                return true;
            }

            return false;
        }

        private static bool IsRightParenthesis(char x)
        {
            if (x == RIGHT_PARENTHESIS)
            {
                return true;
            }

            return false;
        }

        private static bool IsACaret(char x)
        {
            if (x == CARET) 
            {
                return true;
            }

            return false;
        }

        private static bool Contains(Dictionary<char, byte>.KeyCollection collection, char x)
        {
            foreach (var item in collection)
            {
                if (item == x)
                {
                    return true;
                }
            }

            return false;
        }
    }
}
