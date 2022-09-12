extern boolean receive_data_flag;
extern boolean connected_with_slave;
extern boolean ledstatus;
extern boolean coder_mode;
extern int button_result;
extern String code_str_raw;//带;分割号的代码
extern int code_str_raw_item_counter;//当前已录入的程序数量
extern int code_str_raw_item_max;//能储存的最大编程块数量，默认为18
extern String code_str_clean; //真正用来分析的去掉;的代码

extern boolean has_condition_type1;//在存储code_str_condition_type1的同时，将has_condition_type1置为1，没有则为0
extern boolean receive_condition_type1;//在上位机也就是控制器接收到下位机也就是机器人发来的触发了条件1状况时，置位1，执行完毕置为0
extern String code_str_condition_type1;//存储type1符号表示的条件语句，type1 目前为{}中的语句

extern boolean has_condition_type2;
extern boolean receive_condition_type2;//在上位机也就是控制器接收到下位机也就是机器人发来的触发了条件1状况时，置位1，执行完毕置为0
extern String code_str_condition_type2;//存储type2符号表示的条件语句, type2 目前为[]中的语句

extern boolean has_condition_type3;
extern boolean receive_condition_type3;//在上位机也就是控制器接收到下位机也就是机器人发来的触发了条件1状况时，置位1，执行完毕置为0
extern String code_str_condition_type3;//存储type3符号表示的条件语句, type3 目前为||中的语句
extern boolean instant_stop;
extern boolean start_cypher;

extern byte rfid_block_buffer[18];
extern boolean read_new_card;

extern boolean voice_trigger;
extern int voice_type;
extern boolean if_local_process_code;

extern int mode_switch_condition;//0-遥控模式, 1 -编程闯关模式，2-编程积分模式


