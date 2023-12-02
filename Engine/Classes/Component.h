#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H
namespace TEG
{
	class Component
	{
	public:
		virtual void Update(){};
		virtual void Start(){};
		virtual void Stop(){};
		bool GetEnabled() const { return enabled; }
		void SetEnabled(bool enabled_) { enabled = enabled_; }

		// bool operator<(const Component &other) const
		// {
		// 	return this < &other;
		// }

	private:
		bool enabled = true;
	};
}
#endif