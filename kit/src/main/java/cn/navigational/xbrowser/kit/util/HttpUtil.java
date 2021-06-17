package cn.navigational.xbrowser.kit.util;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Optional;
import java.util.logging.Logger;

/**
 * 封装Http请求工具类
 */
public class HttpUtil {
    public static final Integer OK_STATUS_CODE = 200;
    private static final Logger LOGGER = Logger.getLogger(HttpUtil.class.getName());

    /**
     * 发起get请求
     */
    public static <T> Optional<T> doGet(String url, HttpResponse.BodyHandler<T> handlers) {
        var request = HttpRequest.newBuilder().uri(URI.create(url)).GET().build();
        T result = null;
        try {
            var response = HttpClient.newBuilder().build().send(request, handlers);
            if (response.statusCode() == OK_STATUS_CODE) {
                result = response.body();
            }
        } catch (IOException | InterruptedException e) {
            LOGGER.info("HTTP request happen error:" + e.getMessage());
        }
        return Optional.ofNullable(result);
    }
}
