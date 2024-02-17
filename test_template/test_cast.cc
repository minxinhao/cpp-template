struct Base
{
    virtual void foo()
    {
    }
    int x;
};
struct Derived : Base
{
    int y;
};

int get_xy(Base *param)
{
    auto pd = dynamic_cast<Derived *>(param);
    return pd->x * pd->y;
}