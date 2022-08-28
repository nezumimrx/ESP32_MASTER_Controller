#include <Arduino.h>
#include "global_vars.h"
#include <ESPNOW_MASTER.h>
#define forward_pin 16
#define backward_pin 17
#define turn_left_pin 21
#define turn_right_pin 22
#define mec_left 14
#define mec_right 25
#define button_clear 26
#define button_stop 27
#define button_play 32
#define button_back 33
#define coder_switch 13

String button_previous = "";      //用来过滤多余按键检测
String code_button_previous = ""; //编程功能的按键
boolean previous_coder_mode;
void Button_init()
{
    pinMode(15, OUTPUT); //连接指示灯
    pinMode(forward_pin, INPUT_PULLUP);
    pinMode(backward_pin, INPUT_PULLUP);
    pinMode(turn_left_pin, INPUT_PULLUP);
    pinMode(turn_right_pin, INPUT_PULLUP);
    pinMode(mec_left, INPUT_PULLUP);
    pinMode(mec_right, INPUT_PULLUP);
    pinMode(button_clear, INPUT_PULLUP);
    pinMode(button_stop, INPUT_PULLUP);
    pinMode(button_play, INPUT_PULLUP);
    pinMode(button_back, INPUT_PULLUP);
    pinMode(coder_switch, INPUT_PULLUP);

    if (digitalRead(coder_switch) == 1)
    {
        coder_mode = false;
        previous_coder_mode=false;
    }
    else
    {
        coder_mode = true;
        previous_coder_mode=true;
    }
}

String button_read_add_to_str(String str, int pin)
{

    uint8_t read_data = digitalRead(pin);
    str += read_data;
    return str;
}
String delete_last_item()
{
    String deleted_str = "";
    int last_delimiter_index = code_str_raw.lastIndexOf(";");
    deleted_str = code_str_raw.substring(0, last_delimiter_index);
    Serial.println(deleted_str);
    return deleted_str;
}

void count_code_str_raw(){
    int temp_counter=0;
    for(int i=0;i<(code_str_raw.length());i++){
        char c = code_str_raw.charAt(i);
        if(c==';')temp_counter++;
    }
    code_str_raw_item_counter=temp_counter;
}

String remove_delimiters(String str)
{
    String clean_str = "";
    int code_item_counter = 0;
    for (int i = 0; i < (str.length()); i++)
    {
        char c = str.charAt(i);
        if (c != ';')
        {
            clean_str += c;
        }
        else if (c == ';')
        {
            code_item_counter++;
        }
    }
    Serial.println(clean_str);
    Serial.print("counter: ");
    Serial.println(code_item_counter);
    if (code_item_counter > code_str_raw_item_max)
    {
        clean_str = "Oversize";
    }
    return clean_str;
}

int legal_test_simple(String str)
{ //检测语句是否正确特别是当有循环开始(2的时候有没有反括弧)
    int positive_bracket_counter = 0;
    int negetive_bracket_counter = 0;
    if (str.startsWith("Oversize"))
    {
        return 2;
    }
    else
    {
        if (str.length() < 2)
        {
            return 3; //还没有录入编程指令
        }
        else if (str.length() >= 2)
        {
            int bracket_counter = 0;
            for (int i = 0; i < (str.length()); i++)
            {
                char c = str.charAt(i);
                if (c == '(')
                {
                    bracket_counter++;
                    positive_bracket_counter++;
                }
                else if (c == ')')
                {
                    bracket_counter--;
                    negetive_bracket_counter++;
                }
                if (bracket_counter < 0)
                {
                    return 0;
                    break;
                }
            }
            if (positive_bracket_counter == negetive_bracket_counter)
            {
                return 1;
            }
            else
                return 0;
        }
        else
            return 0; //没有可能会发生这种情况，只是让计算机不报warning
    }
}

int check_condition(char condition_symbol_start, char condition_symbol_end, String str)
{ // 0 没有找到符号，1找到符号并且存到对应的code_str_condition_type中并且has_condition_type标志被转为true，同时剔除掉在code_str_clean的部分，2语法错误
    int positive_bracket = str.indexOf(condition_symbol_start);
    int negative_bracket = str.indexOf(condition_symbol_end);

    if (positive_bracket == -1 && negative_bracket == -1)
    {
        
        if(condition_symbol_start=='{'){has_condition_type1 = false;Serial.println("no condition {whatsoever}.");}
        else if(condition_symbol_start=='['){has_condition_type2=false;Serial.println("no condition [whatsoever].");}
        else if(condition_symbol_start=='<'){has_condition_type3=false;Serial.println("no condition <whatsoever>.");}
        return 0; // no condition symbol '{''}'
    }
    else if ((positive_bracket >= 0 && negative_bracket == -1) || (positive_bracket == -1 && negative_bracket >= 0))
    {
        Serial.println("incomplete condition sentence, wrong code");
        return 2; // only have one bracket, wrong code '{' no '}' or no '{' has '}'
    }
    else if (positive_bracket >= 0 && negative_bracket >= 0)
    {
        Serial.println("may be a good code lets proceed to check it.");
        int positve_bracket_counter = 0;
        int negative_bracket_counter = 0;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == condition_symbol_start)
                positve_bracket_counter++;
            if (str[i] == condition_symbol_end)
                negative_bracket_counter++;
        }
        Serial.print("positive bracket counter: ");
        Serial.println(positve_bracket_counter);
        Serial.print("negative bracket counter: ");
        Serial.println(negative_bracket_counter);
        if (positve_bracket_counter != 1 || negative_bracket_counter != 1)
        {
            Serial.println("too many brackets, illegal code");
            return 2;
        }
        else
        {
            if (positive_bracket >= negative_bracket)
            {
                Serial.println("positive bracket goes infront of negative bracket, illegal code");
                return 2;
            }
            else
            {
                String temp_condition_str = str.substring(positive_bracket + 1, negative_bracket);
                Serial.print("temp_condition_str: ");
                Serial.println(temp_condition_str);
                //这里很重要！我们该把裁剪出来的条件语句放到哪个type下的全局变量存储？目前{}是type1，[]是type2,||是type3，后续还可以添加，记得改这里
                if (condition_symbol_start == '{')
                {
                    code_str_condition_type1 = temp_condition_str;
                    has_condition_type1 = true;
                }
                if (condition_symbol_start == '[')
                {
                    code_str_condition_type2 = temp_condition_str;
                    has_condition_type2 = true;
                }
                if (condition_symbol_start == '|')
                {
                    code_str_condition_type3 = temp_condition_str;
                    has_condition_type3 = true;
                }
                code_str_clean.remove(positive_bracket, (negative_bracket - positive_bracket + 1));
                Serial.print("cut out of condition code_str_clean: ");
                Serial.println(code_str_clean);
                return 1;
            }
        }

        return 1;
    }
    else
    {
        Serial.println("i dont know what the fuck just happened,this should not happen");
        return 2;
    }
}

void Button_read()
{
    String button_readStr = "";
    String code_button_readStr = ""; //只记录编程按键
    button_readStr = button_read_add_to_str(button_readStr, forward_pin);
    button_readStr = button_read_add_to_str(button_readStr, backward_pin);
    button_readStr = button_read_add_to_str(button_readStr, turn_left_pin);
    button_readStr = button_read_add_to_str(button_readStr, turn_right_pin);
    button_readStr = button_read_add_to_str(button_readStr, mec_left);
    button_readStr = button_read_add_to_str(button_readStr, mec_right);
    code_button_readStr = button_read_add_to_str(code_button_readStr, button_clear);
    code_button_readStr = button_read_add_to_str(code_button_readStr, button_stop);
    code_button_readStr = button_read_add_to_str(code_button_readStr, button_play);
    code_button_readStr = button_read_add_to_str(code_button_readStr, button_back);
    if (digitalRead(coder_switch) == 1)
    {
        coder_mode = false;
        if (previous_coder_mode == true)
        {
            code_str_raw = "&";
            //播放切换为遥控模式
            Serial.println("切换为遥控模式");
            voice_trigger=true;
            voice_type=20;//切换为遥控模式
            previous_coder_mode = coder_mode;
        }
    }
    else
    {
        coder_mode = true;
        if (previous_coder_mode == false)
        {
            code_str_raw = "&";
            //播放语音切换为编程模式
            Serial.println("切换为编程模式");
            voice_trigger=true;
            voice_type=21;//切换为编程模式
            previous_coder_mode = coder_mode;
        }
    }

    if (button_previous == "111111" && button_readStr == "011111")
    {
        Serial.println("forward");
        button_result = 1;
    }
    else if (button_previous == "111111" && button_readStr == "101111")
    {
        Serial.println("backward");
        button_result = 2;
    }
    else if (button_previous == "111111" && button_readStr == "110111")
    {
        Serial.println("turn left");
        button_result = 3;
    }
    else if (button_previous == "111111" && button_readStr == "111011")
    {
        Serial.println("turn right");
        button_result = 4;
    }
    else if (button_previous == "111111" && button_readStr == "111101")
    {
        Serial.println("mec_left");
        button_result = 5;
    }
    else if (button_previous == "111111" && button_readStr == "111110")
    {
        Serial.println("mec_right");
        button_result = 6;
    }

    if (code_button_previous == "1111" && code_button_readStr == "0111")
    {
        Serial.println("clear");
        button_result = 7;
    }
    else if (code_button_previous == "1111" && code_button_readStr == "1011")
    {
        Serial.println("stop");
        button_result = 8;
    }
    else if (code_button_previous == "1111" && code_button_readStr == "1101")
    {
        Serial.println("play");
        button_result = 9;
    }
    else if (code_button_previous == "1111" && code_button_readStr == "1110")
    {
        Serial.println("back");
        button_result = 10;
    }

    if (button_previous != "111111" && button_readStr == "111111")
    { //松开按键的判定，当上一次还是有信息的button_readstr而这次变成了没有信息的，说明按键松开，似乎只对遥控模式有用把？
        button_result = 99;
    }
    // Serial.println(button_readStr);
    code_button_previous = code_button_readStr;
    button_previous = button_readStr;
    button_readStr = "";
    code_button_readStr = "";
}
void motion_record(String new_item)
{
    if (code_str_raw_item_counter <= code_str_raw_item_max)
    {
        Serial.println("record");
        code_str_raw += new_item;
        voice_trigger = true;
        voice_type = 1; //动作指令卡片
        code_str_raw_item_counter++;
        Serial.println(code_str_raw);
    }
    else
    {
        Serial.println("oversize");
        voice_trigger = true;
        voice_type = 2; //超出上限
    }
}
void Button_functions()
{
    if (button_result != 0)
    {
        // forward
        if (button_result == 1 && coder_mode == 0)
        { //按键按下且不在编程模式
            Serial.println("Button result 1 forward");
            send_data_now('W', 1);
            voice_trigger=true;
            voice_type=14;
            button_result = 0;
        }
        else if (button_result == 1 && coder_mode == 1)
        {
            Serial.println("Add forward command");
            motion_record(";W1");
            button_result = 0;
        }
        // backward
        if (button_result == 2 && coder_mode == 0)
        {
            Serial.println("Button result 2 backward");
            voice_trigger=true;
            voice_type=14;
            send_data_now('W', 2);
            button_result = 0;
        }
        else if (button_result == 2 && coder_mode == 1)
        {
            Serial.println("Add backward command");
            motion_record(";W2");
            button_result = 0;
        }
        // left_turn
        if (button_result == 3 && coder_mode == 0)
        {
            Serial.println("Button result 3 turn_left");
            voice_trigger=true;
            voice_type=14;
            send_data_now('W', 3);
            button_result = 0;
        }
        else if (button_result == 3 && coder_mode == 1)
        {
            Serial.println("Add turnleft command");
            motion_record(";W3");
            button_result = 0;
        }
        // right_turn
        if (button_result == 4 && coder_mode == 0)
        {
            Serial.println("Button result 4 turn_right");
            voice_trigger=true;
            voice_type=14;
            send_data_now('W', 4);
            button_result = 0;
        }
        else if (button_result == 4 && coder_mode == 1)
        {
            Serial.println("Add turnright command");
            motion_record(";W4");
            button_result = 0;
        }
        // mec_move_left
        if (button_result == 5 && coder_mode == 0)
        {
            Serial.println("Button result 5 mec_move_left");
            voice_trigger=true;
            voice_type=14;
            send_data_now('W', 5);
            button_result = 0;
        }
        else if (button_result == 5 && coder_mode == 1)
        {
            Serial.println("Add mec_move_left command");
            motion_record(";W5");
            button_result = 0;
        }
        // mec_move_right
        if (button_result == 6 && coder_mode == 0)
        {
            Serial.println("Button result 6 mec_move_right");
            voice_trigger=true;
            voice_type=14;
            send_data_now('W', 6);
            button_result = 0;
        }
        else if (button_result == 6 && coder_mode == 1)
        {
            Serial.println("Add mec_move_right command");
            motion_record(";W6");
            button_result = 0;
        }
        // stop
        if (button_result == 99 && coder_mode == 0)
        { //松开按键了发送stop
            Serial.println("stop the wheel");
            send_data_now('W', 0);
            button_result = 0;
        }

        // emergent stop
        if (button_result == 8 && coder_mode == 1)
        {
            Serial.println("CodingMode Emergent STOP!");
            instant_stop = 1;
            start_cypher = 0;
            button_result = 0;
            voice_trigger = true;
            voice_type = 3; //紧急停止
            // play voice emergent stop and play emo_stop
            voice_trigger = true;
            voice_type = 3; //紧急停止
            //
        }
        else if (button_result == 7 && coder_mode == 1)
        {
            Serial.println("CodingMode CLEAR!");
            code_str_raw = "&";
            code_str_clean = "";
            button_result = 0;
            // play voice code clear and play emo_clear
            voice_trigger = true;
            voice_type = 4; //清除指令
            //
        }
        else if (button_result == 9 && coder_mode == 1)
        {
            Serial.println("CodingMode RUN/PLAY!");
            // code_str_raw="&(2D02(2D01(3D))D04){(2D03D02)}";//用来测试逻辑的，实际使用要注释掉
            // code_str_raw="&W102W203";//用来测试逻辑的，实际使用要注释掉
            code_str_clean = remove_delimiters(code_str_raw);
            int check_condition_type1_result = check_condition('{', '}', code_str_clean); // 0-没有type1的条件判断符号{}, 1-正确（详细说明看checkcondition功能，2语法错误
            int check_condition_type2_result = check_condition('[', ']', code_str_clean); // 0-没有type2的条件判断符号[], 1-正确（详细说明看checkcondition功能，2语法错误
            int check_condition_type3_result = check_condition('<', '>', code_str_clean); // 0-没有type3的条件判断符号||, 1-正确（详细说明看checkcondition功能，2语法错误
            int legal_result = 0;
            legal_result = legal_test_simple(code_str_clean);
            if (check_condition_type1_result == 1)
                legal_test_simple(code_str_condition_type1);
            else if (check_condition_type1_result == 2)
                legal_result = 0; //语法错误
            if (check_condition_type2_result == 1)
                legal_test_simple(code_str_condition_type2);
            else if (check_condition_type2_result == 2)
                legal_result = 0; //语法错误
            if (check_condition_type3_result == 1)
                legal_test_simple(code_str_condition_type3);
            else if (check_condition_type3_result == 2)
                legal_result = 0; //语法错误
            if (legal_result == 1)
            {
                Serial.println("legal code");
                
                // play voice run and play emo_ragerthat!
                voice_trigger = true;
                voice_type = 6; //运行、启动、开始执行编程指令
                delay(2000);
                //
                instant_stop = 0;
                start_cypher = 1;
            }
            else if (legal_result == 0)
            {
                Serial.println("illegal code");
                // play voice illegal_code and play emo_question mark!
                voice_trigger = true;
                voice_type = 7; //程序有错误
                //
            }
            else if (legal_result == 3)
            {
                Serial.println("empty code");
                // play voice empty_code and play emo_silence!
                voice_trigger = true;
                voice_type = 8; //没有录入程序指令
                //
            }
            else if (legal_result == 2)
            {
                Serial.println("oversize code");
                // play voice oversize_code and play emo 一团乱!
                voice_trigger = true;
                voice_type = 2; //超出上限
                                //
            }
            button_result = 0;
        }
        else if (button_result == 10 && coder_mode == 1)
        {
            Serial.println("Codingmode BACK!");
            code_str_raw = delete_last_item();
            code_str_raw_item_counter--;
            button_result = 0;
            // play voice oversize_code and play emo_exclamation mark
            voice_trigger = true;
            voice_type = 5; //撤销指令
            //
        }
    }
}