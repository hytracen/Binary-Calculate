#include "main.h"
using namespace std;
/*
要求：
1 实现+、-、*、/以及^次方操作
2 能够处理出现括号的情况，包括多重括号的情况
3 能够判断算符的优先级，并自动按照优先级构造二叉树，能够正确处理像 这样的计算式
4 对错误的输入能够进行判断，包括物理错误以及逻辑错误，比如000.567,7/0等
*/

#define Plus 0
#define Minus 1
#define Multiple 2
#define Division 3
#define Pow 4
#define EPS 1e-6 ///< 定义小数运算误差
#define PRINTERROR(condition, text) { if(condition) { cerr<<text<<endl; exit(-1); }} ///< 定义错误输入处理宏


/// \brief 扫描输入字符串，将其转化为Token类型的队列，便于后续处理
/// \param p_string 输入字符串
/// \param p_queue 处理后的队列
void Scan( const char* p_string, queue<Token>& p_queue )
{
    int index = 0;
    int length = strlen( p_string );
    char c;

    Token t{};

    while( index < length )
    {
        // read the character in, and assume it is invalid to begin with.
        c = p_string[index];
        t.m_type = VOID;

        // find out what kind of token it is.
        switch( c )
        {
            // parenthesis
            case '(':
                t.m_type = LPAREN;
                break;
            case ')':
                t.m_type = RPAREN;
                break;

                // operators
            case '+':
                t.m_type = OPERATOR;
                t.m_operator = Plus;
                break;
            case '-':
                // Is negative
                if((index == 0)||(p_string[index-1] == '('))
                {
                    ++index;
                    t.m_type = NUMBER;
                    t.m_number = 0 - ReadFloat( p_string, index );
                    --index;
                }
                    // Is minus
                else
                {
                    t.m_type = OPERATOR;
                    t.m_operator = Minus;
                }
                break;
            case '*':
                t.m_type = OPERATOR;
                t.m_operator = Multiple;
                break;
            case '/':
                t.m_type = OPERATOR;
                t.m_operator = Division;
                break;
            case '^':
                t.m_type = OPERATOR;
                t.m_operator = Pow;
                break;

                // variables
            case 'c':
                t.m_type = VARIABLE;
                t.m_variable = 0;
                break;
            case 's':
                t.m_type = VARIABLE;
                t.m_variable = 1;
                break;
            case 't':
                t.m_type = VARIABLE;
                t.m_variable = 2;
                break;
            case 'l':
                t.m_type = VARIABLE;
                t.m_variable = 3;
                break;

                // numbers
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                t.m_type = NUMBER;
                t.m_number = ReadFloat( p_string, index );
                index--;
                break;

            default:
                // 如果存在其它字符，则输入格式错误
            PRINTERROR(true, "格式错误")
                break;
        }

        // if the token was valid, enqueue it.
        if( t.m_type != VOID )
        {
            if(!p_queue.empty())
            {
                PRINTERROR(p_queue.back().m_type == OPERATOR && t.m_type == OPERATOR, "格式错误")
            }
            p_queue.push( t );
        }

        index++;
    }
}

/// \brief 从输入字符串中的p_index位置起读取一个浮点数
/// \param p_string 输入的字符串
/// \param p_index 指定需要读取的位置
/// \return 返回读取的浮点数
float ReadFloat( const char* p_string, int& p_index )
{
    float f = 0.0f;
    char c = p_string[p_index];
    float divisor = 10.0f;

//     如果小数点位于浮点数的第一个字符处，则返回格式错误
    PRINTERROR(c=='.', "格式错误")

    // read the front part of the float in first
    while( c >= '0' && c <= '9' )
    {
        // multiply the current float by 10, then
        // add the current character to the current float
        // (ie: if f was 1.0 and c is '4', then after these
        // steps, f will be 10.0, then 14.0)
        f *= 10.0f;
        f += (float)(c - '0');

        // read the next character
        p_index++;
        c = p_string[p_index];
    }

    // load the back part of the float, if there is a period
    if( c == '.' )
    {
        p_index++;
        c = p_string[p_index];

        // while there are numbers, read them in
        while( c >= '0' && c <= '9' )
        {
            // add "c/divisor" to the float.
            // when this starts out, divisor is 10,
            // so if the first number after the period is 3,
            // then this adds 3/10 to the float. Then
            // it multiplies the divisor by 10, so if the next
            // number is 7, it adds 7/100, and so on.
            f += (float)(c - '0') / divisor;

            // multiply the divisor by 10.
            divisor *= 10.0f;

            // read the next char
            p_index++;
            c = p_string[p_index];

        }
    }
    return f;
}

/// \brief 处理优先级最低的 + - 运算
/// \param Expression 输入的表达式队列
/// \return 可用于计算表达式值的二叉树
BinaryTree<Token>* ExcExpression(queue<Token>& Expression){
    auto* Root = ExcItem(Expression);
    while(!Expression.empty())
    {
        Token CenterToken = Expression.front();
        if(CenterToken.m_type == OPERATOR)
        {
            if(CenterToken.m_operator == Plus || CenterToken.m_operator == Minus)
            {
                auto *TempRoot = new BinaryTree<Token>;
                TempRoot->m_data = CenterToken;
                TempRoot->m_left = Root;
                Root = TempRoot;

                Expression.pop();
                Root->m_right = ExcItem(Expression);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    return Root;
}

/// \brief 处理优先级次高的 * / ^表达式
/// \param Expression 输入的表达式队列
/// \return 可用于计算表达式值的二叉树
BinaryTree<Token>* ExcItem(queue<Token>& Expression){
    auto* Root = ExcFactor(Expression);
    while(!Expression.empty())
    {
        Token CenterToken = Expression.front();
        if(CenterToken.m_type == OPERATOR)
        {
            if(CenterToken.m_operator == Multiple || CenterToken.m_operator == Division || CenterToken.m_operator == Pow)
            {
                auto *TempRoot = new BinaryTree<Token>;
                TempRoot->m_data = CenterToken;
                TempRoot->m_left = Root;
                Root = TempRoot;

                Expression.pop();
                Root->m_right = ExcFactor(Expression);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    return Root;
}

/// \brief 处理优先级最高的含括号或单数值的表达式
/// \param Expression 输入的表达式队列
/// \return 可用于计算表达式值的二叉树
BinaryTree<Token>* ExcFactor(queue<Token>& Expression){
    BinaryTree<Token>* Root;
    Token LeftToken = Expression.front();
    // 检验因子左侧是否为错误的右括号
    PRINTERROR(LeftToken.m_type == RPAREN, "括号不匹配")

    if(LeftToken.m_type == LPAREN)
    {
        Expression.pop();
        Root = ExcExpression(Expression);
        // 检验括号是否匹配
        PRINTERROR(Expression.front().m_type != RPAREN, "括号不匹配")
        Expression.pop();
    }
    else
    {
        //Number
        Root = new BinaryTree<Token>;
        Root->m_data = Expression.front();
        Expression.pop();
    }
    return Root;
}

/// \brief 处理输入的表达式二叉树的值，并返回计算结果
/// \param p_tree 输入的表达式二叉树
/// \return 计算结果
float Evaluate( BinaryTree<Token>* p_tree )
{
    // if the tree node is invalid, return 0.
    if( p_tree == 0 )
        return 0.0f;

    float left = 0.0f;
    float right = 0.0f;

    switch( p_tree->m_data.m_type )
    {
//        case VARIABLE:
//            // if a variable, return the value of the variable
//            return g_vars[p_tree->m_data.m_variable];
//            break;
        case NUMBER:
            // if a number, return the number
            return p_tree->m_data.m_number;
            break;
        case OPERATOR:
            // if an operator, evaluate the left and right children, then
            // perform the operation on them.
            left = Evaluate( p_tree->m_left );
            right = Evaluate( p_tree->m_right );
            switch( p_tree->m_data.m_operator )
            {
                case Plus:
                    return left + right;
                    break;
                case Minus:
                    return left - right;
                    break;
                case Multiple:
                    return left * right;
                    break;
                case Division:
                    PRINTERROR(abs(right) <= EPS, "除数不能为零")
                    return left / right;
                    break;
                case Pow:
                    return pow(left, right);
                    break;
            }
        case VOID:
            break;
        case VARIABLE:
            break;
        case LPAREN:
            break;
        case RPAREN:
            break;
    }
    return 0.0f;
}

/// \brief 层序遍历打印二叉树
/// \param Root 待打印二叉树的根节点
void PrintBinaryTree( BinaryTree<Token>* Root)
{
    queue<BinaryTree<Token>* > BFS;
    int LevelIndex = 1;
    if(Root)
    {
        BFS.push(Root);
    }
    while(!BFS.empty())
    {
        int LevelSize = BFS.size();
        cout<<"Level"<<LevelIndex<<": ";
        for(int i=LevelSize; i>0; --i)
        {
            BinaryTree<Token>* TempNode = BFS.front();
            BFS.pop();
            switch (TempNode->m_data.m_type)
            {
                case NUMBER:
                    cout<<TempNode->m_data.m_number;
                    break;
                case OPERATOR:
                    switch (TempNode->m_data.m_operator)
                    {
                        case Plus:
                            cout<<'+';
                            break;
                        case Minus:
                            cout<<'-';
                            break;
                        case Multiple:
                            cout<<'*';
                            break;
                        case Division:
                            cout<<'/';
                            break;
                        case Pow:
                            cout<<'^';
                            break;
                    }
                    break;
                default:
                    break;
            }
            cout<<" ";
            if(TempNode->m_left)
            {
                BFS.push(TempNode->m_left);
            }
            if(TempNode->m_right)
            {
                BFS.push(TempNode->m_right);
            }
        }
        ++LevelIndex;
        cout<<endl;
    }

}

int main(){
    BinaryTree<Token>* Root;
    queue<Token> Expression;
    cout<<"输入运算符表达式(不要输入等号和空格,输入\"Exit\"结束):"<<endl;
    string InputStr;
    cin>>InputStr;
    while (InputStr != "Exit")
    {
        Scan(InputStr.c_str(), Expression);
        Root = ExcExpression(Expression);
        cout<<Evaluate(Root)<<endl;
        cout<<"二叉树层序输出结果如下:"<<endl;
        PrintBinaryTree(Root);

        cout<<"输入运算符表达式(不要输入等号和空格,输入\"Exit\"结束):"<<endl;
        cin>>InputStr;
    }
    return 0;
}