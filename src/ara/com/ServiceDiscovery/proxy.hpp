// not used any more


class proxy
{
private:
    /* data */
    int server_port_number; // to save the received port number from the service discovery
public:
    proxy(/* args */);
    ~proxy();
    int Create(int portNumber, int service_id);
    int Method();
};

