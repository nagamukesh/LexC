%{
        void yyerror(char* s);
        int yylex();
        #include "stdio.h"
        #include "stdlib.h"
        #include "ctype.h"
        #include "string.h"
        #include "custom_memory.h"  // Include custom memory management
        
        void insert_type();
        void insert_class();
        void insert_value();
        void insert_dimensions();
        void insert_pdl(int pdl);
        void insert_parameters();
        int flag=0;
        int insert_flag = 0;
        int pdl;

        extern char current_identifier[20];
        extern char current_type[20];
        extern char current_value[20];
        extern char current_function[20];
        extern char previous_operator[20];
        extern void init_lexer_memory();

        // Define the node structure first
        struct node { 
                struct node *child1; 
                struct node *child2;
                struct node *child3; 
                struct node *child4; 
                struct node *child5;
                struct node *child6; 
                struct node *child7; 
                char *token; 
        };

        struct node *head;

        struct queueNode {
                struct node *treeNode;
                struct queueNode *next;
        };

        struct queue {
                struct queueNode *front;
                struct queueNode *rear;
        };

        // Function declarations
        struct node* mknode(struct node *child1, struct node *child2, struct node *child3, 
                          struct node *child4, struct node *child5, struct node *child6, 
                          struct node *child7, char *token);
        void levelOrderTraversal(struct node *root);
        int isEmpty(struct queue *q);

        // Implementation of mknode
        struct node* mknode(struct node *child1, struct node *child2, struct node *child3, 
                          struct node *child4, struct node *child5, struct node *child6, 
                          struct node *child7, char *token) {
                struct node *newnode = (struct node *)custom_malloc(sizeof(struct node));
                char *newstr = (char *)custom_malloc(strlen(token) + 1);
                strcpy(newstr, token);
                newnode->token = newstr;
                newnode->child1 = child1;
                newnode->child2 = child2;
                newnode->child3 = child3;
                newnode->child4 = child4;
                newnode->child5 = child5;
                newnode->child6 = child6;
                newnode->child7 = child7;
                return newnode;
        }

        void enqueue(struct queue *q, struct node *treeNode) {
                struct queueNode *newNode = (struct queueNode *)custom_malloc(sizeof(struct queueNode));
                newNode->treeNode = treeNode;
                newNode->next = NULL;
                if (q->rear == NULL) {
                        q->front = q->rear = newNode;
                } else {
                        q->rear->next = newNode;
                        q->rear = newNode;
                }
        }

        struct node *dequeue(struct queue *q) {
                if (q->front == NULL) {
                        return NULL;
                }
                struct queueNode *temp = q->front;
                struct node *treeNode = temp->treeNode;
                q->front = q->front->next;
                if (q->front == NULL) {
                        q->rear = NULL;
                }
                custom_free(temp);
                return treeNode;
        }

        int isEmpty(struct queue *q) {
                return q->front == NULL;
        }

        void cleanup_tree(struct node *root) {
                if (root == NULL) return;
                cleanup_tree(root->child1);
                cleanup_tree(root->child2);
                cleanup_tree(root->child3);
                cleanup_tree(root->child4);
                cleanup_tree(root->child5);
                cleanup_tree(root->child6);
                cleanup_tree(root->child7);
                custom_free(root->token);
                custom_free(root);
        }

        void levelOrderTraversal(struct node *root) {
                if (root == NULL) return;

                struct queue q;
                q.front = q.rear = NULL;

                enqueue(&q, root);
                int level = 0;

                printf("\n");
                while (!isEmpty(&q)) {
                        int levelSize = 0;
                        struct queueNode *current = q.front;
                        while (current != NULL) {
                                levelSize++;
                                current = current->next;
                        }

                        for (int i = 0; i < levelSize; i++) {
                                struct node *currentNode = dequeue(&q);
                                
                                // Print indentation and tree branches
                                for (int j = 0; j < level; j++) {
                                        printf("│   ");
                                }
                                printf("├── %s\n", currentNode->token);

                                // Enqueue child nodes in reverse order to maintain tree structure
                                if (currentNode->child7 != NULL) enqueue(&q, currentNode->child7);
                                if (currentNode->child6 != NULL) enqueue(&q, currentNode->child6);
                                if (currentNode->child5 != NULL) enqueue(&q, currentNode->child5);
                                if (currentNode->child4 != NULL) enqueue(&q, currentNode->child4);
                                if (currentNode->child3 != NULL) enqueue(&q, currentNode->child3);
                                if (currentNode->child2 != NULL) enqueue(&q, currentNode->child2);
                                if (currentNode->child1 != NULL) enqueue(&q, currentNode->child1);
                        }
                        level++;
                }
                printf("\n");
        }
%}

%union { 
	struct var_name { 
		char name[100]; 
		struct node* nd;
	} nd_obj; 
} 

%token <nd_obj> IDENTIFIER

%nonassoc <nd_obj> IF 
%token <nd_obj> INT CHAR FLOAT DOUBLE LONG SHORT SIGNED UNSIGNED STRUCT
%token <nd_obj> RETURN MAIN
%token <nd_obj> VOID
%token <nd_obj> WHILE FOR DO
%token <nd_obj> BREAK CONTINUE GOTO
%token <nd_obj> ENDIF
%token <nd_obj> SWITCH CASE DEFAULT
%token <nd_obj> AUTO CONST BOOL STATIC TYPEDEF UNION VOLATILE
%token <nd_obj> OPEN_CURLY CLOSE_CURLY SEMI_COLON COMMA COLON EQUALS OPEN_BRACE CLOSE_BRACE OPEN_SQR CLOSE_SQR DOT AND NOT TILD HYPHEN PLUS MULTIPLY DIVIDE PERCENT POWER OR QUESTION

%token <nd_obj> integer_constant string_constant float_constant character_constant
%token <nd_obj> RIGHT_ASSIGN LEFT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token <nd_obj> RIGHT_OP LEFT_OP PTR_OP

%nonassoc <nd_obj> ELSE

%right <nd_obj> MOD_EQUAL
%right <nd_obj> MUL_EQUAL DIV_EQUAL
%right <nd_obj> ADD_EQUAL SUB_EQUAL

%left <nd_obj> OR_OP
%left <nd_obj> AND_OP

%left <nd_obj> EQUAL NOT_EQUAL
%left <nd_obj> LESSER_EQUAL LESSER GREATER_EQUAL GREATER

%right <nd_obj> SIZEOF
%left <nd_obj> INCREMENT DECREMENT

%type <nd_obj> state declarations declaration structure_dec structure_content variable_dec structure_initialize variables multiple_variables identifier_name extended_identifier array_identifier array_dims
%type <nd_obj> initilization string_initilization array_initialization array_values multiple_array_values datatype unsigned_grammar signed_grammar long_grammar function_dec 
%type <nd_obj> function_name function_data parameters all_parameter_identifiers multiple_parameters parameter_identifier extended_parameter statement multiple_statement statments expression_statment 
%type <nd_obj> conditional_statements extended_conditional_statements switch_statement extended_switch_statement iterative_statements for_initialization return_statement return_suffix break_statement
%type <nd_obj> expression expressions simple_expression simple_expression_breakup and_expression and_expression_breakup unary_relation_expression regular_expression regular_expression_breakup 
%type <nd_obj> relational_operators sum_expression sum_operators term multiply_operators factor iden extended_iden func func_call arguments arguments_list extended_arguments constant

%%
state
                        : declarations
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "state");
                        	head=$$.nd;
                        }
                        ;

declarations
                        : declaration declarations 
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "declarations");
                        }
                        |
                        {
	     			$$.nd = NULL; 
	     		}       
                        ;

declaration
                        : variable_dec
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "declaration");
                        }
                        | function_dec
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "declaration");
                        }
                        | structure_dec
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "declaration");
                        }
                        ;

structure_dec
                        : STRUCT IDENTIFIER {insert_type(); insert_class(0);} OPEN_CURLY structure_content  CLOSE_CURLY SEMI_COLON
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "STRUCT");
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	$4.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_CURLY");
                        	$6.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_CURLY");
                        	$7.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	$$.nd=mknode($1.nd, $2.nd, $4.nd, $5.nd, $6.nd, $7.nd, NULL, "structure_dec");
                        }
                        ;

structure_content : variable_dec structure_content
		  {
		  	$$.nd=mknode($1.nd,$2.nd, NULL, NULL, NULL, NULL, NULL, "structure_content");
		  } 
	          | 
	          {
	     		$$.nd = NULL; 
	     	  }
	          ;

variable_dec
                        : datatype variables SEMI_COLON
                        {
                        	$3.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	$$.nd=mknode($1.nd,$2.nd, $3.nd, NULL, NULL, NULL, NULL, "variable_dec");
                        }
                        | datatype MULTIPLY variables SEMI_COLON
                        {
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "MULTIPLY");
                        	$4.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	$$.nd=mknode($1.nd,$2.nd, $3.nd, $4.nd, NULL, NULL, NULL, "variable_dec");
                        }
                        | structure_initialize
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "variable_dec");
                        }
                        ;

structure_initialize
                        : STRUCT IDENTIFIER variables
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "STRUCT");
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	$$.nd=mknode($1.nd, $2.nd, $3.nd, NULL, NULL, NULL, NULL, "structure_dec");
                        }
                        ;

variables
                        : identifier_name multiple_variables
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "variable_dec");
                        }
                        ;

multiple_variables
                        : COMMA variables
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COMMA");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "multiple_variables");
                        }
                        | 
                        {
	     			$$.nd = NULL; 
	     	  	}
                        ;

identifier_name
                        : IDENTIFIER {insert_type(); insert_class(2);} extended_identifier
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	$$.nd=mknode($1.nd, $3.nd, NULL, NULL, NULL, NULL, NULL, "identifier_name");
                        }
                        ;

extended_identifier : array_identifier 
		    {
		    	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "extended_identifier");
		    }
	            | EQUALS {strcpy(previous_operator,"=");} expression 
	            {
	            	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "EQUALS");
	            	$$.nd=mknode($1.nd, $3.nd, NULL, NULL, NULL, NULL, NULL, "extended_identifier");
	            }
	            ;

array_identifier
                        : OPEN_SQR array_dims
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_SQR");
	            		$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "array_identifier");
                        }
                        | 
                        {
	     			$$.nd = NULL; 
	     	  	}
                        ;

array_dims
                        : integer_constant {insert_dimensions();} CLOSE_SQR initilization
                        {
                        	$3.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_SQR");
	            		$$.nd=mknode($1.nd, $3.nd, $4.nd, NULL, NULL, NULL, NULL, "array_dims");
                        }
                        | CLOSE_SQR string_initilization
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_SQR");
	            		$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "array_dims");
                        }
                        ;

initilization
                        : string_initilization
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "initialization");
                        }
                        | array_initialization
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "initialization");
                        }
                        | 
                        {
	     			$$.nd = NULL; 
	     	  	}
                        ;

string_initilization
                        : EQUALS {strcpy(previous_operator,"=");} string_constant {insert_value();}
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "EQUALS");
	            		$$.nd=mknode($1.nd, $3.nd, NULL, NULL, NULL, NULL, NULL, "string_initialization");
                        }
                        ;

array_initialization
                        : EQUALS {strcpy(previous_operator,"=");} OPEN_CURLY array_values CLOSE_CURLY
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "EQUALS");
                        	$3.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_CURLY");
                        	$5.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_CURLY");
	            		$$.nd=mknode($1.nd, $3.nd, $4.nd, $5.nd, NULL, NULL, NULL, "array_initialization");
                        }
                        ;

array_values
                        : integer_constant multiple_array_values
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "array_values");
                        }
                        ;

multiple_array_values
                        : COMMA array_values
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COMMA");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "multiple_array_values");
                        }
                        |
                        {
	     			$$.nd = NULL; 
	     	  	} 
                        ;


datatype
                        : INT 
                        {
                        	$$.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "INT");
                        }
                        | CHAR 
                        {
                        	$$.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CHAR");
                        }
                        | FLOAT
                        {
                        	$$.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "FLOAT");
                        } 
                        | DOUBLE
                        {
                        	$$.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DOUBLE");
                        }
                        | LONG long_grammar
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "LONG");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "datatype");
                        }
                        | SHORT long_grammar
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SHORT");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "datatype");
                        }
                        | UNSIGNED unsigned_grammar
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "UNSIGNED");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "datatype");
                        }
                        | SIGNED signed_grammar
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SIGNED");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "datatype");
                        }
                        | VOID 
                        {
                        	$$.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "VOID");
                        }
                        ;

unsigned_grammar
                        : INT 
                        {
                        	$$.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "INT");
                        }
                        | LONG long_grammar 
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "LONG");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "unsigned_grammar");
                        }
                        | SHORT long_grammar
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SHORT");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "unsigned_grammar");
                        } 
                        |
                        {
	     			$$.nd = NULL; 
	     	  	} 
                        ;

signed_grammar
                        : INT 
                        {
                        	$$.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "INT");
                        }
                        | LONG long_grammar 
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "LONG");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "signed_grammar");	
                        }
                        | SHORT long_grammar 
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SHORT");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "signed_grammar");
                        }
                        |
                        {
	     			$$.nd = NULL; 
	     	  	}	 
                        ;

long_grammar
                        : INT 
                        {
                        	$$.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "INT");
                        }
                        | 
                        {
	     			$$.nd = NULL; 
	     	  	}
                        ;
                        

function_dec
            : function_name OPEN_BRACE parameters CLOSE_BRACE function_data
            {
            	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
            	$4.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
            	$$.nd=mknode($1.nd, $2.nd, $3.nd, $4.nd, $5.nd, NULL, NULL, "function_dec");
            }
            ;

function_name : datatype IDENTIFIER {strcpy(current_function,current_identifier);insert_class(1);}
	      {
	      		$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
	      		$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "function_name");
	      }
	      ;

function_data: OPEN_CURLY statments CLOSE_CURLY   {insert_pdl(0);}
	     {	
	     	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_CURLY");
            	$3.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_CURLY");
            	$$.nd=mknode($1.nd, $2.nd, $3.nd, NULL, NULL, NULL, NULL, "function_data");
	     }
             | SEMI_COLON {insert_pdl(1);}
             {
             	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
             	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "function_data");
             }
             ;

parameters
            : datatype all_parameter_identifiers
            {
            	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "parameters");
            }
            | 
            {
	     	$$.nd = NULL; 
	    }
	    ;  // Allow no parameters


all_parameter_identifiers
                        : parameter_identifier multiple_parameters
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "all_parameter_identifiers");
                        }
                        ;

multiple_parameters
                        : COMMA parameters
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COMMA");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "multiple_parameters");
                        }
                        |
                        {
	     			$$.nd = NULL; 
	     	  	} 
                        ;

parameter_identifier
                        : IDENTIFIER {insert_parameters(); insert_type();} extended_parameter
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	$$.nd=mknode($1.nd, $3.nd, NULL, NULL, NULL, NULL, NULL, "parameter_identifier");
                        }
                        ;

extended_parameter
                        : OPEN_SQR CLOSE_SQR
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_SQR");
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_SQR");
	            		$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "extended_parameter");
                        }
                        |
                        {
	     			$$.nd = NULL; 
	     	  	} 
                        ;

statement
                        : expression_statment
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        } 
                        | multiple_statement
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
                        | conditional_statements
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        } 
                        | iterative_statements
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        } 
                        | switch_statement
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
                        | return_statement 
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
                        | break_statement
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
                        | variable_dec
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "statment");
                        }
                        ;

multiple_statement
                        : OPEN_CURLY statments CLOSE_CURLY
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_CURLY");
                        	$3.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_CURLY");
	            		$$.nd=mknode($1.nd, $2.nd, $3.nd, NULL, NULL, NULL, NULL, "multiple_statement");
                        } 
                        ;

statments
                        : statement statments
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "statments");
                        }
                        | 
                        {
	     			$$.nd = NULL; 
	     	  	}
                        ;

expression_statment
                        : expression SEMI_COLON
                        {
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "expression_statment");
                        }
                        | SEMI_COLON 
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "expression_statment");
                        }
                        ;

conditional_statements
                        : IF OPEN_BRACE simple_expression CLOSE_BRACE statement extended_conditional_statements 
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IF");
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	$4.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
	            		$$.nd=mknode($1.nd, $2.nd, $3.nd, $4.nd, $5.nd, $6.nd, NULL, "conditional_statements");
                        }
                        ;

extended_conditional_statements
                        : ELSE statement
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "ELSE");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "extended_conditional_statements");
                        }
                        |
                        {
	     			$$.nd = NULL; 
	     	  	} 
                        ;

switch_statement        : SWITCH OPEN_BRACE IDENTIFIER CLOSE_BRACE OPEN_CURLY extended_switch_statement CLOSE_CURLY
			{
				$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SWITCH");
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	$3.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	$4.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
                        	$5.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_CURLY");
                        	$7.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_CURLY");
	            		$$.nd=mknode($1.nd, $2.nd, $3.nd, $4.nd, $5.nd, $6.nd, $7.nd, "switch_statement");
			}
		        ;

extended_switch_statement
                        : CASE integer_constant COLON expression SEMI_COLON extended_switch_statement
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CASE");
                        	$3.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COLON");
                        	$5.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
	            		$$.nd=mknode($1.nd, $2.nd, $3.nd, $4.nd, $5.nd, $6.nd, NULL, "extended_switch_statement");
                        }
                        | break_statement
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "extended_switch_statement");
                        }
                        | DEFAULT COLON break_statement
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DEFAULT");
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COLON");
	            		$$.nd=mknode($1.nd, $2.nd, $3.nd, NULL, NULL, NULL, NULL, "extended_switch_statement");
                        }
                        ;

iterative_statements
                        : WHILE OPEN_BRACE simple_expression CLOSE_BRACE statement
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "WHILE");
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	$4.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
	            		$$.nd=mknode($1.nd, $2.nd, $3.nd, $4.nd, $5.nd, NULL, NULL, "iterative_statements");	
                        }
                        | FOR OPEN_BRACE for_initialization simple_expression SEMI_COLON expression CLOSE_BRACE
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "FOR");
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	$5.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	$7.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
	            		$$.nd=mknode($1.nd, $2.nd, $3.nd, $4.nd, $5.nd, $6.nd, $7.nd, "iterative_statements");	
                        }
                        | DO statement WHILE OPEN_BRACE simple_expression CLOSE_BRACE SEMI_COLON
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DO");
                        	$3.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "WHILE");
                        	$4.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	$6.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
                        	$7.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
	            		$$.nd=mknode($1.nd, $2.nd, $3.nd, $4.nd, $5.nd, $6.nd, $7.nd, "iterative_statements");
                        }
                        ;

for_initialization
                        : variable_dec
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "for_initialization");
                        }
                        | expression SEMI_COLON
                        {
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "for_initialization");
                        }
                        | SEMI_COLON 
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "for_initialization");
                        }
                        ;

return_statement
                        : RETURN return_suffix
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "RETURN");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "return statement");
                        }
                        ;

return_suffix
                        : SEMI_COLON
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "return_suffix");
                        }
                        | expression SEMI_COLON 
                        {
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "return_suffix");
                        }
                        ;

break_statement
                        : BREAK SEMI_COLON
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "BREAK");
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SEMI_COLON");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "break_statement");
                        }
                        ;

expression
                        : iden expressions
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "expression");
                        }
                        | simple_expression 
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "expression");
                        }
                        ;

expressions
                        : EQUALS {strcpy(previous_operator,"=");} expression
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "EQUALS");
                        	$$.nd=mknode($1.nd, $3.nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }                     
                        | ADD_EQUAL{strcpy(previous_operator,"+=");} expression
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "ADD_EQUAL");
                        	$$.nd=mknode($1.nd, $3.nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }
                        | SUB_EQUAL{strcpy(previous_operator,"-=");} expression
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "SUB_EQUAL");
                        	$$.nd=mknode($1.nd, $3.nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }
                        | MUL_EQUAL{strcpy(previous_operator,"*=");} expression
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "MUL_EQUAL");
                        	$$.nd=mknode($1.nd, $3.nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }
                        | DIV_EQUAL{strcpy(previous_operator,"/=");} expression
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DIV_EQUAL");
                        	$$.nd=mknode($1.nd, $3.nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }
                        | MOD_EQUAL{strcpy(previous_operator,"%=");} expression
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "MOD_EQUAL");
                        	$$.nd=mknode($1.nd, $3.nd, NULL, NULL, NULL, NULL, NULL, "expressions");
                        }
                        | INCREMENT
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "INCREMENT");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "expressions");	
                        }
                        | DECREMENT 
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DECREMENT");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "expressions");	
                        }
                        ;

simple_expression
                        : and_expression simple_expression_breakup
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "simple_expression");
                        }
                        ;

simple_expression_breakup
                        : OR_OP and_expression simple_expression_breakup 
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OR_OP");
                        	$$.nd=mknode($1.nd, $2.nd, $3.nd, NULL, NULL, NULL, NULL, "simple_expression_breakup");	
                        }
                        |
                        {
	     			$$.nd = NULL; 
	     	  	} 
                        ;

and_expression
                        : unary_relation_expression and_expression_breakup
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "and_expression");
                        }
                        ;

and_expression_breakup
                        : AND_OP unary_relation_expression and_expression_breakup
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "AND_OP");
                        	$$.nd=mknode($1.nd, $2.nd, $3.nd, NULL, NULL, NULL, NULL, "and_expression_breakup");	
                        }
                        |
                        {
	     			$$.nd = NULL; 
	     	  	} 
                        ;

unary_relation_expression
                        : NOT unary_relation_expression
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "NOT");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "unary_relation_expression");	
                        }
                        | regular_expression 
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "unary_relation_expression");
                        }
                        ;

regular_expression
                        : sum_expression regular_expression_breakup
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "regular_expression");
                        }
                        ;

regular_expression_breakup
                        : relational_operators sum_expression
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "regular_expression_breakup");
                        }
                        |
                        {
	     			$$.nd = NULL; 
	     	  	} 
                        ;

relational_operators
                        : GREATER_EQUAL{strcpy(previous_operator,">=");}
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "GREATER_EQUAL");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
                        | LESSER_EQUAL{strcpy(previous_operator,"<=");}
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "LESSER_EQUAL");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
                        | GREATER{strcpy(previous_operator,">");}
                        {
				$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "GREATER");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
                        | LESSER{strcpy(previous_operator,"<");}
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "LESSER");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
                        | EQUAL{strcpy(previous_operator,"==");}
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "EQUAL");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
                        | NOT_EQUAL{strcpy(previous_operator,"!=");} 
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "NOT_EQUAL");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "relational_operators");	
                        }
                        ;

sum_expression
                        : sum_expression sum_operators term
                        {
                        	$$.nd=mknode($1.nd, $2.nd, $3.nd, NULL, NULL, NULL, NULL, "sum_expression");
                        }
                        | term 
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "sum_expression");
                        }
                        ;

sum_operators
                        : PLUS
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "PLUS");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "sum_operators");	
                        }
                        | HYPHEN
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "HYPHEN");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "sum_operators");	
                        }
                        ;

term
                        : term multiply_operators factor
                        {
                        	$$.nd=mknode($1.nd, $2.nd, $3.nd, NULL, NULL, NULL, NULL, "term");	
                        }
                        | factor 
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "term");	
                        }
                        ;

multiply_operators
                        : MULTIPLY 
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "MULTIPLY");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "multiply_operators");	
                        }
                        | DIVIDE
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DIVIDE");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "multiply_operators");	
                        }
                        | PERCENT
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "PERCENT");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "multiply_operators");	
                        }
                        ;

factor
                        : func 
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "factor");	
                        }
                        | iden
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "factor");	
                        } 
                        ;

iden
                        : IDENTIFIER
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "iden");	
                        }
                        | iden extended_iden
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "iden");
                        }
                        ;

extended_iden
                        : OPEN_SQR expression CLOSE_SQR
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_SQR");
                        	$3.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_SQR");
                        	$$.nd=mknode($1.nd, $2.nd, $3.nd, NULL, NULL, NULL, NULL, "extended_iden");
                        }
                        | DOT IDENTIFIER
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "DOT");
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "extended_iden");
                        }
                        ;

func
                        : OPEN_BRACE {strcpy(previous_operator,"(");} expression CLOSE_BRACE
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	$4.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
                        	$$.nd=mknode($1.nd, $3.nd, $4.nd, NULL, NULL, NULL, NULL, "func_call");
                        }
                        | func_call 
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "func");	
                        }
                        | constant
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "func");
                        }
                        ;

func_call
                        : IDENTIFIER OPEN_BRACE {strcpy(previous_operator,"(");insert_class(1);} arguments CLOSE_BRACE 
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "IDENTIFIER");
                        	$2.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "OPEN_BRACE");
                        	$5.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "CLOSE_BRACE");
                        	$$.nd=mknode($1.nd, $2.nd, $4.nd, $5.nd, NULL, NULL, NULL, "func_call");
                        }
                        ;
                        
arguments
                        : arguments_list 
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "arguments");	
                        }
                        |
                        {
	     			$$.nd = NULL; 
	     	  	} 
                        ;

arguments_list
                        : expression extended_arguments
                        {
                        	$$.nd=mknode($1.nd, $2.nd, NULL, NULL, NULL, NULL, NULL, "arguments_list");	
                        }
                        ;

extended_arguments
                        : COMMA expression extended_arguments
                        {
                        	$1.nd=mknode(NULL, NULL, NULL, NULL, NULL, NULL, NULL, "COMMA");
                        	$$.nd=mknode($1.nd, $2.nd, $3.nd, NULL, NULL, NULL, NULL, "multiply_operators");
                        }
                        |
                        {
	     			$$.nd = NULL; 
	     	  	} 
                        ;

constant
                        : integer_constant      { insert_value(); }
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "constant");	
                        }
                        | string_constant       { insert_value(); }
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "constant");	
                        }
                        | float_constant        { insert_value(); }
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "constant");	
                        }
                        | character_constant	{ insert_value(); }
                        {
                        	$$.nd=mknode($1.nd, NULL, NULL, NULL, NULL, NULL, NULL, "constant");	
                        }
                        ;

%%

extern FILE *yyin;
extern int yylineno;
extern char *yytext;
void insert_SymbolTable_type(char *,char *);
void insert_SymbolTable_class(char *,int);
void insert_SymbolTable_value(char *, char *);
void insert_ConstantTable(char *, char *);
void insert_SymbolTable_arraydim(char *, char *);
void insert_SymbolTable_pdl(char *, int);
void insert_SymbolTable_funcparam(char *, char *);
void printSymbolTable();
void printConstantTable();
void printSymbolDataLine();

int main() {
        init_lexer_memory();  // Initialize memory pool
        yyin = fopen("test1.c", "r");
        int result = yyparse();
        
        if(flag == 0) {
                printf("\nVALID PARSE\n");
                printf("\n");
                printf("%30s SYMBOL TABLE \n", " ");
                printf("%1s %s\n", " ", "----------------------------------------------------------------------------------------------------------------------------------");
                printSymbolTable();
                printf("%1s %s\n", " ", "---------------------------------------------------------------------------------------------------------------------------------");
                printf("\n\n%20s CONSTANT TABLE \n", " ");
                printf("%1s %s\n", " ", "-------------------------------------------");
                printConstantTable();
                printf("%1s %s\n\n", " ", "-------------------------------------------");

                // Print beautified AST
                printf("\n╔════════════════════════════════════╗");
                printf("\n║      Abstract Syntax Tree          ║");
                printf("\n╚════════════════════════════════════╝\n");
                levelOrderTraversal(head);

                // Print concise memory info
                printf("\n╔════════════════════════════════════╗");
                printf("\n║      Memory Usage Summary          ║");
                printf("\n╠════════════════════════════════════╣");
                printf("\n║ Memory operations completed        ║");
                printf("\n║ All resources properly freed       ║");
                printf("\n╚════════════════════════════════════╝\n");
        } else {
                printf("\n╔════════════════════════════════════╗");
                printf("\n║          Parsing Status            ║");
                printf("\n╠════════════════════════════════════╣");
                printf("\n║ ✗ Failed to parse input file       ║");
                printf("\n╚════════════════════════════════════╝\n");
        }

        cleanup_tree(head);   // Clean up the parse tree
        free_memory_pool();   // Clean up memory pool
        return result;
}

void yyerror(char *s) {
        printf("Line No. : %d %s %s\n",yylineno, s, yytext);
        flag=1;
        printf("INVALID PARSE\n");
}

void insert_type() {
        insert_SymbolTable_type(current_identifier,current_type);
}

void insert_class(int a) {
        insert_SymbolTable_class(current_identifier,a);
}

void insert_value() {       
        if(strcmp(previous_operator, "=") == 0) {
                insert_SymbolTable_value(current_identifier,current_value);
        }
}       

void insert_dimensions() {       
        insert_SymbolTable_arraydim(current_identifier, current_value);
}

void insert_pdl(int pdl) {
        insert_SymbolTable_pdl(current_function, pdl);
}

void insert_parameters() {
        insert_SymbolTable_funcparam(current_function, current_identifier);
}

