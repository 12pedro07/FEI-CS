#include "../headers/table.h"
#include "../headers/philosopher.h"
#include <windows.h>
#include <string>

class Table;
unsigned int Philosopher::TIME2EAT = 0;
unsigned int Philosopher::TIME2THINK = 0;

Philosopher::Philosopher(int _chair, Table* _table) 
    : chair(_chair), table(_table)
{
    this->left_fork = false;
    this->right_fork = false;
    this->current_state = Philosopher::hungry;
}

void Philosopher::Iterate()
{
    switch (this->current_state)
    {
        case Philosopher::eating :
            Sleep(Philosopher::TIME2EAT);
            this->ReturnForks();
            this->ChangeState(Philosopher::thinking);
            break;

        case Philosopher::thinking :
            Sleep(Philosopher::TIME2THINK);
            this->ChangeState(Philosopher::hungry);
            break;

        case Philosopher::hungry :
            this->GetFork();
            if (this->CountForks() == 2)
            {
                this->ChangeState(Philosopher::eating);
                return;
            }
            break;
        default:
            break;
    }
}

void Philosopher::ChangeState(Philosopher::state new_state)
{
    this->current_state = new_state;
}

void Philosopher::GetFork()
{
    // Verifica e pega na mesa os garfos disponiveis
    switch (this->table->GetFork(this->chair))
    {
    case fork_type::LEFT_FORK :
        this->left_fork = true;
        break;
    case fork_type::RIGHT_FORK :
        this->right_fork = true;
        break;
    case fork_type::NO_FORK :
        break;
    default:
        break;
    }
}

void Philosopher::ReturnForks()
{
   this->table->ReturnForks(this->chair);
   this->left_fork = false;
   this->right_fork = false;
}

int Philosopher::CountForks()
{
    return (int)(this->right_fork + this->left_fork);
}

bool Philosopher::HoldingLeftFork()
{
    return this->left_fork;
}

bool Philosopher::HoldingRightFork()
{
    return this->right_fork;
}

std::string Philosopher::GetState()
{
    switch (this->current_state)
    {
        case Philosopher::eating :
            return "Eating  ";
        case Philosopher::thinking :
            return "Thinking";
        case Philosopher::hungry :
            return "Hungry  ";
        case Philosopher::dead :
            return "Dead    ";
    }

    return "ERROR";
}

void Philosopher::Simulate(Philosopher* philosopher)
{
    while (philosopher->current_state != Philosopher::dead)
    {
        philosopher->Iterate();
    }
}