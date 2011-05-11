/*
Initialize the stack with S
Read input symbol
while (true)
    if Action(top(stack), input) = S
    如果是移位
         NS <- Goto(top(stack),input)
         push NS
         Read next symbol
         
    else if Action(top(stack), input) = Rk
    如果是化简
         output k
         pop |RHS| of production k from stack
         NS <- Goto(top(stack), LHS_k)
         push NS
         
    else if Action(top(stack),input) = A //接受
         output valid, return
    else                                 //拒绝
         output invalid, return
*/

// goto_table

// action_table
#include <stdio.h>
#define states_num 10
#define inputs_num 6
#define TRUE 1
#define FALSE 0

// 终结符
char terminals[inputs_num] = {'+', '-', '[', ']', 'a', '#'};

char non_termials[] = {'F'};

int goto_table[states_num] = {2, 5, -1, 7, -1, -1, 8, -1, -1, -1};

char * action_table[states_num][inputs_num] = {
	{"  ", "s1", "s3", "  ", "s4", "  ",},
	{"  ", "s1", "s3", "  ", "s4", "  ",},
	{"s6", "  ", "  ", "  ", "  ", "ac",},
	{"  ", "s1", "s3", "  ", "s4", "  ",},
	{"r1", "  ", "  ", "r1", "  ", "r1",},
	{"r2", "  ", "  ", "r2", "  ", "r2",},
	{"  ", "s1", "s3", "  ", "s4", "  ",},
	{"s6", "  ", "  ", "s9", "  ", "  ",},
	{"r3", "  ", "  ", "r3", "  ", "r3",},
	{"r4", "  ", "  ", "r4", "  ", "r4",},
};

char * reduce_rule[4] = {
	"F~a",
	"F~-F",
	"F~F+F",
	"F~[F]",
};

char stack[50];
int top = 0;

void push(char c)
{
	stack[top++] = c;
}

char pop(void)
{
	if (top >= 0)
		return stack[top--];
	else
		return '#';
}

char get_top(void)
{
	return stack[top - 1];
}

int get_row_of_action(char terminal)
{
	for (int i = 0; i < inputs_num; i++) {
		if (terminals[i] == terminal)
			return i;
	}
	return -1;
}

int slr(char *input)
{
	int i = 0;
	char *action, state;;
	int action_row, goto_state, rule;
	
	while (input[i] != '#') {
		// 获得动作
		action_row = get_row_of_action(input[i]);
		state = get_top();
		action = action_table[state - '0'][action_row];
		printf("action = %s\n", action);
		// 处理
		if (*action == 's') {
			// 移位
			push(input[i]);
			push(action[1]);
			
		} else if (*action == 'r') {
			// 化简
			rule = action[1] - '0';
			for (int i = 0; *(reduce_rule[rule] + 1 + i) != '\0'; i++) {
				pop();
				pop();
			}
			state = get_top();
			goto_state = goto_table[state - '0']; //只有一个变元
			push('F');
			push(goto_state + '0');
			
		} else if (*action == 'a') {
			// 接受
			return TRUE;
			
		} else {
			// 拒绝
			return FALSE;
		}
		i++;
	}
	return TRUE;
}



//char *test_input = "[a+a+a]+[-a+a+a]+[a+-a+a]+[-a+-a+a]#";
char *test_input = "a#";

int main(void)
{
	top = 0;
	push('#');
	push('0');
	int a = 0;
	if (test_input[0] == '#') {
		printf("OK 1\n");
	} else {
		a = slr(test_input);
		printf("OK? %d\n", a);
	}
	return 0;
}

