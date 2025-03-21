//
// Created by 吴 歆韵 on 2025/3/20.
//

#ifndef COMPACT_USET_CORE_H
#define COMPACT_USET_CORE_H
#include <vector>
#include <cstdint>
#include <limits>
#include <cassert>
#include <ranges>
#include <algorithm>

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
        explicit Set(U maximum = 0);

        void insert(U);
        auto contains(U value) const {return _hash[value] != numeric_limits<U>::max();}
        void remove(U);
        void clear();

        auto begin() const {return _data.begin();}
        auto end() const {return _data.end();}

        U size() const {return _data.size();}
        auto get_data_list() const -> const vector<U>& {return _data;}
        auto get_hash_list() const -> const vector<U>& {return _hash;}

        void re_set(U);
        void check() const;

        auto operator==(const Set&) const ->bool;
    };

    template<UnsignedInt U>
    void Set<U>::re_set(U new_maximum) {
        assert(new_maximum > _hash.size());
        _hash.resize(new_maximum+1, numeric_limits<U>::max());
    }

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
    auto Set<U>::operator==(const Set& other) const -> bool {
        if (_data.size() != other._data.size()) return false;
        auto size {std::min(_hash.size(), other._hash.size())};
        for (auto i{0}; i<size; ++i) {
            if (!(_hash[i] == std::numeric_limits<U>::max() && other._hash[i] == std::numeric_limits<U>::max()
                ||
                _hash[i] < std::numeric_limits<U>::max() && other._hash[i] < std::numeric_limits<U>::max())
            ) return false;
        }
        return true;
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
    void Set<U>::clear() {
        _data.clear();
        std::ranges::fill(_hash, numeric_limits<U>::max());
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
        if (maximum == 0) return;
        _hash.resize(maximum + 1, numeric_limits<U>::max());
    }

}
#endif //COMPACT_USET_CORE_H
