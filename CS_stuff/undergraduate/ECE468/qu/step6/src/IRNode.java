public class IRNode {
        
        public enum IROp {
                ADDI,
                ADDF,
                SUBI,
                SUBF,
                MULTI,
                MULTF,
                DIVI,
                DIVF,
                STOREI,
                STOREF,
                GT,
                GE,
                LT,
                LE,
                NE,
                EQ,
                JUMP,
                LABEL,
                READI,
                READF,
                WRITEI,
                WRITEF,
                WRITES,
                JSR,
                PUSH,
                POP,
                RET,
                LINK
        }
        
        public IROp opCode;
        public String op1;
        public String op2;
        public String result;
        public boolean isFloat;
}