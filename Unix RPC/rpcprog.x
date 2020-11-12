struct send_data{

  double a;
  int Y<>;

};

struct receive_data{

  double double_arr<>;
  int int_arr<2>;

};

program AVG_PROG{
  version AVG_VERS{
    double AVG(send_data) = 1;
  } = 1;
} = 0x23451111;

program MIN_MAX_PROG{
  version MIN_MAX_VERS{
    receive_data MIN_MAX(send_data) = 2;
  } = 1;
} = 0x23451112;

program MUL_PROG{
  version MUL_VERS{
    receive_data MUL(send_data) = 3;
  } = 1;
} = 0x23451113;
