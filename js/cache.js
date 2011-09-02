var IterMemoFib = function() {
    var cache = [1, 1];

    return function (n) {
        if (n >= cache.length) {
            for (var i = cache.length; i < n ; i++ ) {
                cache[i] = cache[i - 2] + cache[i - 1];
            }
        }
        return cache[n - 1];
    }
}();
