namespace TEG
{
	class Component
	{
	public:
		virtual void Update(){};
		virtual void Start(){};
		virtual void Stop(){};
		bool GetEnabled() { return enabled; }
		void SetEnabled(bool enabled_) { enabled = enabled_; }

	private:
		bool enabled;
	};
}