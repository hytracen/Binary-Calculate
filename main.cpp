#include "main.h"
using namespace std;
/*
Ҫ��
1 ʵ��+��-��*��/�Լ�^�η�����
2 �ܹ�����������ŵ�����������������ŵ����
3 �ܹ��ж���������ȼ������Զ��������ȼ�������������ܹ���ȷ������ �����ļ���ʽ
4 �Դ���������ܹ������жϣ�������������Լ��߼����󣬱���000.567,7/0��
*/

#define Plus 0
#define Minus 1
#define Multiple 2
#define Division 3
#define Pow 4
#define EPS 1e-6 ///< ����С���������
#define PRINTERROR(condition, text) { if(condition) { cerr<<text<<endl; exit(-1); }} ///< ����������봦���


/// \brief ɨ�������ַ���������ת��ΪToken���͵Ķ��У����ں�������
/// \param p_string �����ַ���
/// \param p_queue �����Ķ���
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
                // ������������ַ����������ʽ����
            PRINTERROR(true, "��ʽ����")
                break;
        }

        // if the token was valid, enqueue it.
        if( t.m_type != VOID )
        {
            if(!p_queue.empty())
            {
                PRINTERROR(p_queue.back().m_type == OPERATOR && t.m_type == OPERATOR, "��ʽ����")
            }
            p_queue.push( t );
        }

        index++;
    }
}

/// \brief �������ַ����е�p_indexλ�����ȡһ��������
/// \param p_string ������ַ���
/// \param p_index ָ����Ҫ��ȡ��λ��
/// \return ���ض�ȡ�ĸ�����
float ReadFloat( const char* p_string, int& p_index )
{
    float f = 0.0f;
    char c = p_string[p_index];
    float divisor = 10.0f;

//     ���С����λ�ڸ������ĵ�һ���ַ������򷵻ظ�ʽ����
    PRINTERROR(c=='.', "��ʽ����")

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

/// \brief �������ȼ���͵� + - ����
/// \param Expression ����ı��ʽ����
/// \return �����ڼ�����ʽֵ�Ķ�����
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

/// \brief �������ȼ��θߵ� * / ^���ʽ
/// \param Expression ����ı��ʽ����
/// \return �����ڼ�����ʽֵ�Ķ�����
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

/// \brief �������ȼ���ߵĺ����Ż���ֵ�ı��ʽ
/// \param Expression ����ı��ʽ����
/// \return �����ڼ�����ʽֵ�Ķ�����
BinaryTree<Token>* ExcFactor(queue<Token>& Expression){
    BinaryTree<Token>* Root;
    Token LeftToken = Expression.front();
    // ������������Ƿ�Ϊ�����������
    PRINTERROR(LeftToken.m_type == RPAREN, "���Ų�ƥ��")

    if(LeftToken.m_type == LPAREN)
    {
        Expression.pop();
        Root = ExcExpression(Expression);
        // ���������Ƿ�ƥ��
        PRINTERROR(Expression.front().m_type != RPAREN, "���Ų�ƥ��")
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

/// \brief ��������ı��ʽ��������ֵ�������ؼ�����
/// \param p_tree ����ı��ʽ������
/// \return ������
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
                    PRINTERROR(abs(right) <= EPS, "��������Ϊ��")
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

/// \brief ���������ӡ������
/// \param Root ����ӡ�������ĸ��ڵ�
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
    cout<<"������������ʽ(��Ҫ����ȺźͿո�,����\"Exit\"����):"<<endl;
    string InputStr;
    cin>>InputStr;
    while (InputStr != "Exit")
    {
        Scan(InputStr.c_str(), Expression);
        Root = ExcExpression(Expression);
        cout<<Evaluate(Root)<<endl;
        cout<<"��������������������:"<<endl;
        PrintBinaryTree(Root);

        cout<<"������������ʽ(��Ҫ����ȺźͿո�,����\"Exit\"����):"<<endl;
        cin>>InputStr;
    }
    return 0;
}