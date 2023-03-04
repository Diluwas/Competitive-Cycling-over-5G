package com.coap;

import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.SocketException;

import org.eclipse.californium.core.CoapServer;
import org.eclipse.californium.core.config.CoapConfig;
import org.eclipse.californium.core.network.CoapEndpoint;
import org.eclipse.californium.core.server.resources.CoapExchange;
import org.eclipse.californium.core.server.resources.MyIpResource;
import org.eclipse.californium.elements.config.Configuration;
import org.eclipse.californium.elements.config.UdpConfig;
import org.eclipse.californium.elements.util.NetworkInterfacesUtil;
import org.eclipse.californium.core.coap.CoAP.Type;


public class CoAPSampleServer extends CoapServer{
		
	private void addEndpoints(boolean udp,int port) {
		Configuration config = Configuration.getStandard();
		for (InetAddress addr : NetworkInterfacesUtil.getNetworkInterfaces()) {
			InetSocketAddress bindToAddress = new InetSocketAddress(addr, port);
			if (udp) {
				CoapEndpoint.Builder builder = new CoapEndpoint.Builder();
				builder.setInetSocketAddress(bindToAddress);
				builder.setConfiguration(config);
				addEndpoint(builder.build());
			}
		}
	}
	
	public static void main(String[] args) throws SocketException {
		// create server
		boolean udp = true;
		int port = Configuration.getStandard().get(CoapConfig.COAP_PORT);
		CoAPSampleServer server = new CoAPSampleServer();
		getTheTime time = new getTheTime("time");
		server.add(time);
		server.addEndpoints(udp,port);		// add endpoints on all IP addresses
		server.start();
	}
	
	
}
