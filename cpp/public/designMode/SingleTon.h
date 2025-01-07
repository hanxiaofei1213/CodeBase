#pragma once

template <typename T>
class SingleTon {
public:
	static T& getInstance() {
		static T obj;
		return obj;
	}

protected:
	SingleTon() = default;
	SingleTon(const SingleTon&) = delete;
	SingleTon& operator=(const SingleTon&) = delete;

};