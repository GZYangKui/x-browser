package cn.navigational.xbrowser.kit.downloader;

import cn.navigational.xbrowser.kit.util.HttpUtil;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpHeaders;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

/**
 * 文件下载工具类
 */
public class XDownloadHelper {
    /**
     * 当前连接是否下载连接
     */
    public static boolean checkDownload(String location) {
        var request = HttpRequest.newBuilder().uri(URI.create(location)).build();
        final HttpResponse<Void> response;
        try {
            response = HttpClient.newHttpClient().send(request, HttpResponse.BodyHandlers.discarding());
        } catch (IOException | InterruptedException e) {
            throw new RuntimeException(e);
        }
        return response.statusCode() == HttpUtil.OK_STATUS_CODE && checkDownloadHeader(response.headers());
    }

    /**
     * 检查http请求头是否下载请求
     */
    private static boolean checkDownloadHeader(HttpHeaders headers) {
        var list = headers.map().get("Content-Type");
        if (list.isEmpty()) {
            return false;
        }
        var content = list.get(0);
        if (content.contains("application")) {
            return true;
        } else if (content.contains("video")) {
            return true;
        } else if (content.contains("audio")) {
            return true;
        } else {
            return content.contains("image");
        }
    }
}
