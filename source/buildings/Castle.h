#ifndef SOURCE_BUILDINGS_CASTLE_H_
#define SOURCE_BUILDINGS_CASTLE_H_

#include <base/Building.h>

// Defines the castle building
class Castle : public Building {
 public:
    Castle(const Castle&)            = default;
    ~Castle()                        = default;
    Castle(Castle&&)                 = default;
    Castle& operator=(const Castle&) = default;
    Castle& operator=(Castle&&)      = default;

    void Build() override;

    void ShowUI() override;

    void Attack() override;

    void TakeDamage() override;

    void Destroy() override;
};

#endif  // SOURCE_BUILDINGS_CASTLE_H_
