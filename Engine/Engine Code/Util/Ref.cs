namespace TEG.Util
{
    public class Ref<T> where T : class?
    {
        public T? Value { get; set; }
    }
}