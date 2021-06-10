package cn.navigational.xplayer.kit;

import cn.navigational.xplayer.kit.util.StringUtil;

import java.net.URI;
import java.util.HashMap;
import java.util.Map;

public class Location {
    private int port;
    private String url;
    private String host;
    private String protocol;
    private Map<String, String> queries;

    private Location() {
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getHost() {
        return host;
    }

    public void setHost(String host) {
        this.host = host;
    }

    public String getProtocol() {
        return protocol;
    }

    public void setProtocol(String protocol) {
        this.protocol = protocol;
    }

    public int getPort() {
        return port;
    }

    public void setPort(int port) {
        this.port = port;
    }

    public Map<String, String> getQueries() {
        return queries;
    }

    public void setQueries(Map<String, String> queries) {
        this.queries = queries;
    }

    public String httpRoot() {
        var sb = new StringBuilder();
        sb.append(protocol);
        sb.append("://");
        sb.append(host);
        if (port != -1) {
            sb.append(":");
            sb.append(port);
        }
        sb.append("/");
        return sb.toString();
    }

    public String favicon() {
        return httpRoot() + "/favicon.ico";
    }

    public static Location create(String str) {
        var uri = URI.create(str);
        var location = new Location();
        location.setUrl(uri.getPath());
        location.setHost(uri.getHost());
        location.setPort(uri.getPort());
        location.setProtocol(uri.getScheme());
        location.setQueries(new HashMap<>());
        if (StringUtil.isEmpty(uri.getQuery())) {
            return location;
        }
        var arr = uri.getQuery().split("&");
        for (String query : arr) {
            var entry = query.split("=");
            if (entry.length != 2) {
                continue;
            }
            location.getQueries().put(entry[0], entry[1]);
        }
        return location;
    }

}
