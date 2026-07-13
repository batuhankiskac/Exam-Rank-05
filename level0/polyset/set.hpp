#include "searchable_bag.hpp"

// "wrapping" (sarama) işlemi, genellikle bir sınıfın (class) başka bir sınıfı,
// fonksiyonu ya da veriyi içine alarak bir arayüz (interface) sağlaması anlamına gelir.
// REFERANSLA SARMA
class set
{
	private:
		searchable_bag& bag;
	public:
		set() = delete;
		set(const set& source) = delete;
		set& operator=(const set& source) = delete;
		set(searchable_bag& s_bag);

		bool has(int) const;
		void insert (int);
		void insert (int *, int);
		void print() const;
		void clear();

		const searchable_bag& get_bag();

		~set();

};
