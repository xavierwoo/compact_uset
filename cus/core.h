//
// Created by 吴 歆韵 on 2025/3/20.
//

#ifndef COMPACT_USET_CORE_H
#define COMPACT_USET_CORE_H
#include <vector>
#include <cstdint>
#include <limits>
#include <cassert>

namespace compact_uset {

    void it_works();

    template<typename U>
    concept UnsignedInt = (std::is_same_v<U, uint8_t> ||
                           std::is_same_v<U, uint16_t> ||
                           std::is_same_v<U, uint32_t> ||
                           std::is_same_v<U, uint64_t>);

    using std::vector;
    using std::numeric_limits;

    template<UnsignedInt U = uint32_t>
    struct Set {
    private:
        vector<U> _hash;
        vector<U> _data;
    public:
        explicit Set(U);

        void insert(U);
        auto contains(U value) const {return _hash[value] != numeric_limits<U>::max();}
        void remove(U);

        auto begin() const {return _data.begin();}
        auto end() const {return _data.end();}

        U size() const {return _data.size();}
        auto get_data_list() const -> const vector<U>& {return _data;}
        auto get_hash_list() const -> const vector<U>& {return _hash;}

        void check() const;
    };

    template<UnsignedInt U>
    void Set<U>::check() const {
        U count {0};
        for (auto i{0}; i<_hash.size(); ++i){
            if (_hash[i] == numeric_limits<U>::max()) continue;
            assert(_data[_hash[i]] == i);
            ++count;
        }
        assert(count == _data.size());
    }

    template<UnsignedInt U>
    void Set<U>::remove(U value) {
        assert(value < _hash.size());
        if (!contains(value)) return;
        auto pos {_hash[value]};
        _hash[value] = numeric_limits<U>::max();
        if(pos < _data.size() - 1){
            auto last {_data.back()};
            _data[pos] = last;
            _hash[last] = pos;
        }
        _data.pop_back();
    }

    template<UnsignedInt U>
    void Set<U>::insert(U value) {
        assert(value < _hash.size());
        if (contains(value)) return;
        _hash[value] = _data.size();
        _data.push_back(value);
    }

    template<UnsignedInt U>
    Set<U>::Set(U maximum) {
        _hash.resize(maximum + 1, numeric_limits<U>::max());
    }

}
#endif //COMPACT_USET_CORE_H
