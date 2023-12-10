import { Module } from "./hello.min.js"

export const prexRawMatch = (regex, string)=> {
    if (regex instanceof RegExp){
        regex = regex.source
    }
    return JSON.parse(
        Module.ccall("getCapturedGroups", "string", ["string", "string"], [ regex, string ])
    )
}
