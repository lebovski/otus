#include <limits>
#include <vector>
#include <cmath>
#include "interface.h"

class Min : public IStatistics
{
public:
    Min() : m_min{std::numeric_limits<double>::max()} {}

    void update(double next) override
    {
        if (next < m_min)
        {
            m_min = next;
        }
    }

    double eval() const override { return m_min; }
    const char *name() const override { return "min"; }

private:
    double m_min;
};

class Max : public IStatistics
{
public:
    Max() : m_max{std::numeric_limits<double>::min()} {}

    void update(double next) override
    {
        if (next > m_max)
        {
            m_max = next;
        }
    }

    double eval() const override { return m_max; }
    const char *name() const override { return "max"; }

private:
    double m_max;
};

class Mean : public IStatistics
{
public:
    Mean() : count{0}, sum{0} {}

    void update(double next) override
    {
        count += 1;
        sum += next;
    }

    double eval() const override { return sum / count; }
    const char *name() const override { return "mean"; }

private:
    double sum;
    double count;
};

class Std : public IStatistics
{
public:
    Std() : mean{}, vec{} {}

    void update(double next) override
    {
        vec.push_back(next);
        mean.update(next);
    }

    double eval() const override
    {
        auto m = mean.eval();
        double variance{0};

        for (std::vector<double>::size_type i = 0; i != vec.size(); i++)
        {
            variance += (vec[i] - m) * (vec[i] - m);
        }
        variance /= vec.size();

        return std::sqrt(variance);
    }

    const char *name() const override { return "std"; }

private:
    std::vector<double> vec;
    Mean mean;
};
