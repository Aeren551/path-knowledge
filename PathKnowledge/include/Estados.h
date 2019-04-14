#ifndef ESTADOS_H
#define ESTADOS_H


class Estados
{
    public:
        static Estados * Instance();
        virtual ~Estados();
        int getEstado();
        void setEstado(int e);

    protected:
        Estados();
        Estados(const Estados & );
        Estados &operator= (const Estados & );

    private:
        static Estados * pinstance;
        int estado;
};

#endif // ESTADOS_H
